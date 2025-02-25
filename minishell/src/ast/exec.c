#include "minishell.h"

static void	free_char_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

static char	*build_cmd_path(char *cmd, t_ht *env)
{
	int		i;
	char	**paths;
	char	*full_path;
	char	*path;

	path = ht_get(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			break ;
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (free_char_matrix(paths), full_path);
		free(full_path);
	}
	free_char_matrix(paths);
	return (NULL);
}

void	append_to_result(char **result, const char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

void	expand_variable(const char *token, int *i, char **result, t_ht *env)
{
	char	key[256];
	char	*value;
	int		j;

	j = 0;
	++(*i);
	if (token[*i] == '{')
	{
		++(*i);
		while (token[*i] && token[*i] != '}')
			key[j++] = token[(*i)++];
		key[j] = '\0';
		++(*i);
	}
	else
	{
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
			key[j++] = token[(*i)++];
		key[j] = '\0';
	}
	value = ht_get(env, key);
	if (value)
		append_to_result(result, value);
	--(*i);
}

void	expand_wildcard(char **result)
{
	DIR				*dir;
	struct dirent	*entry;
	
	dir = opendir(".");
	if (dir)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] != '.')
			{
				append_to_result(result, entry->d_name);
				append_to_result(result, " ");
			}
		}
		closedir(dir);
	}
}

static void handle_quotes(const char *token, int *i, bool *in_single_quotes, bool *in_double_quotes)
{
	if (token[*i] == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (token[*i] == '"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
	if (token[*i] == '\'' || token[*i] == '"')
		++(*i);
}

char	*expand_text(const char *token, t_ht *env)
{
	char	*result;;
	bool	in_single_quotes;
	bool	in_double_quotes;
	int		i;
	char	char_str[2];

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = -1;
	in_double_quotes = false;
	in_single_quotes = false;
	while (token[++i])
	{
		handle_quotes(token, &i, &in_single_quotes, &in_double_quotes);
		if (token[i] == '$' && !in_single_quotes)
			expand_variable(token, &i, &result, env);
		else if (token[i] == '*' && !in_single_quotes && !in_double_quotes)
			expand_wildcard(&result);
		else
		{
			char_str[0] = token[i];
			char_str[1] = '\0';
			append_to_result(&result, char_str);
		}
	}
	return (result);
}

int	handle_redirections(t_list *redir_lst, t_ht *env)
{
	int				fd;
	char			*target;
	t_redirection	*redir;

	while (redir_lst)
	{
		redir = (t_redirection *)redir_lst->content;
		target = expand_text(redir->target, env);
		if (!target)
			return (1);
		if (redir->type == T_INPUT)
			fd = open(target, O_RDONLY);
		else if (redir->type == T_OUTPUT)
			fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_APPEND)
			fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == T_HEREDOC)
			// TODO: add heredoc handler
			fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC);
		if (redir->type == T_HEREDOC || redir->type == T_INPUT)
			dup2(fd, STDIN_FILENO);
		else if (redir->type == T_APPEND || redir->type == T_OUTPUT)
			dup2(fd, STDOUT_FILENO);
		free(target);
		target = NULL;
		if (fd < 0)
			return (1);
		close(fd);
		redir_lst = redir_lst->next;
	}
	return (0);
}

bool is_builtin(const char *cmd)
{
	size_t	i;
	size_t		len;
	char	*lower_cmd;
	bool	builtin;

	if (!cmd)
		return (false);
	len = ft_strlen(cmd);
	lower_cmd = (char *)malloc((len + 1) * sizeof (char));
	if (!lower_cmd)
		return (false);
	i = -1;
	while (++i < len)
		lower_cmd[i] = ft_tolower(cmd[i]);
	lower_cmd[i] = '\0';
	builtin = (!ft_strcmp(lower_cmd, "echo") || !ft_strcmp(lower_cmd, "cd")
		|| !ft_strcmp(lower_cmd, "pwd") || !ft_strcmp(lower_cmd, "unset")
		|| !ft_strcmp(lower_cmd, "export") || !ft_strcmp(lower_cmd, "env")
		|| !ft_strcmp(lower_cmd, "exit"));
	free(lower_cmd);
	return (builtin);
}

void	exec_non_builtin(t_ast *node, t_ht *env)
{
	int		i;
	char	**envp;
	char	*cmd_name;
	char	*error_msg;

	node->cmd->name = expand_text(node->cmd->name, env);
	cmd_name = build_cmd_path(node->cmd->name, env);
	if (!cmd_name)
	{
		error_msg = ft_strjoin("minishell: ", node->cmd->name);
		if (!error_msg)
		{
			free(node->cmd->name);
			exit(127);
		}
		perror(error_msg);
		free(error_msg);
		free(node->cmd->name);
		exit(127);
	}
	free(node->cmd->name);
	i = -1;
	while (node->cmd->args[++i])
		node->cmd->args[i] = expand_text(node->cmd->args[i], env);
	envp = ht_to_matrix(env);
	execve(cmd_name, node->cmd->args, envp);
	perror("minishell");
	exit(1);
}

int	exec_builtin(t_ast *node, t_ht *env)
{
	int		saved_stdin;
	int		saved_stdout;
//	int		status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(node->cmd->redirections, env) != 0) 
	{
		perror("minishell");
		return (1);
	}
//	status = exec_builtin(node, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
//	return (status);
	return (0);
}

int	execute_command(t_ast *node, t_ht *env)
{
	pid_t	pid;
	int		status;

	if (is_builtin(node->cmd->name)) 
		return (exec_builtin(node, env));
	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(node->cmd->redirections, env))
		{
			perror("minishell");
			exit(1);
		}
		if (node->token == T_CMD)
			exec_non_builtin(node, env);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("minishell");
		return -1;
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (-1);
	}
}

int	execute_pipe_side(t_ast *node, t_ht *env, int pipefd[2], int side)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (side == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		exit(execute_ast(node, env));
	}
	else if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("minishell");
		return -1;
	}
	return (pid);
}

int	execute_pipe(t_ast *node, t_ht *env)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		left_status;
	int		right_status;

	if (pipe(pipefd))
		return (perror("minishell"), -1);
	left_pid = execute_pipe_side(node->left, env, pipefd, 0);
	if (left_pid < 0)
		return (-1);
	right_pid = execute_pipe_side(node->right, env, pipefd, 1);
	if (right_pid < 0)
		return (-1);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	return (-1);
}

static int	execute_ast_impl(t_ast *node, t_ht *env)
{
	int	left_status;

	if (!node)
		return (0);
	if (node->token == T_CMD || node->token == T_NONE)
		return (execute_command(node, env));
	if (node->token == T_PIPE)
		return (execute_pipe(node, env));
	if (node->token == T_AND)
	{
		left_status = execute_ast(node->left, env);
		if (left_status == 0)
			return (execute_ast(node->right, env));
		return (left_status);
	}
	if (node->token == T_OR)
	{
		left_status = execute_ast(node->left, env);
		if (left_status != 0)
			return (execute_ast(node->right, env));
		return (left_status);
	}
	return (1);
}

int	execute_ast(t_ast *node, t_ht *env)
{
	pid_t   pid;
	int	 	status;

	if (!node)
		return (0);
	if (node->is_subshell)
	{
		pid = fork();
		if (pid == 0)
		{
			status = execute_ast_impl(node, env);
			exit(status);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	return (execute_ast_impl(node, env));
}
