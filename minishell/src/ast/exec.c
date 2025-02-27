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

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (NULL);
		}
	}
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (NULL);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	append_to_result(t_char_arr *arr, char *new_item)
{
	char	**tmp;
	size_t	i;

	tmp = (char **)malloc((arr->size + 2) * sizeof (char *));
	i = -1;
	while (++i < arr->size)
		tmp[i] = arr->arr[i];
	tmp[i++] = new_item;
	tmp[i] = NULL;
	free(arr->arr);
	arr->arr = tmp;
	++(arr->size);
}

void	append_str(char **result, const char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

void	split_and_append(t_char_arr *result, const char *str)
{
	char	**tokens;
	int		i;

	tokens = ft_split(str, ' ');
	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i])
		append_to_result(result, tokens[i]);
	free(tokens);
}

char	*extract_var_name(const char *token, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i + 1;
	if (token[start] == '?')
		return (*i = start, ft_strdup("?"));
	if (token[start] == '$')
		return (*i = start, ft_strdup("$"));
	len = 0;
	while (ft_isalnum(token[start + len]) || token[start + len] == '_')
		len++;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(token, start, len);
	if (!var_name)
		return (NULL);
	*i = start + len - 1;
	return (var_name);
}

void	expand_variable(const char *token, int *i, char **current, t_ht *env)
{
	char	*key;
	char	*value;

	key = extract_var_name(token, i);
	if (!key)
		return ;
	value = ht_get(env, key);
	if (value)
		append_str(current, value);
	free(key);
}

void	expand_wildcard(t_char_arr *result)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] != '.')
				append_to_result(result, ft_strdup(entry->d_name));
		}
		closedir(dir);
	}
}

static void handle_quotes(const char *token, int *i, bool *in_single_quotes, bool *in_double_quotes)
{
	if (token[*i] == '\'' && !(*in_double_quotes))
	{
		*in_single_quotes = !(*in_single_quotes);
		++(*i);
	}
	else if (token[*i] == '"' && !(*in_single_quotes))
	{
		*in_double_quotes = !(*in_double_quotes);
		++(*i);
	}
}

t_char_arr	*expand_text(const char *token, t_ht *env)
{
	t_char_arr	*result;
	bool		in_single_quotes;
	bool		in_double_quotes;
	int			i;
	char		*current;
	char		token_char[2];

	result = (t_char_arr *)ft_calloc(1, sizeof(t_char_arr));
	if (!result)
		return (NULL);
	current = ft_strdup("");
	if (!current)
		return (free(result), NULL);
	i = -1;
	in_double_quotes = false;
	in_single_quotes = false;
	while (token[++i])
	{
		handle_quotes(token, &i, &in_single_quotes, &in_double_quotes);
		if (!token[i])
			break ;
		if (token[i] == '$' && !in_single_quotes)
		{
			expand_variable(token, &i, &current, env);
			if (!in_double_quotes)
			{
				split_and_append(result, current);
				if (result->size > 0)
				{
					current = result->arr[result->size - 1];
					result->size--;
				}
				else
					current = ft_strdup("");
			}
		}
		else if (token[i] == '*' && !in_single_quotes && !in_double_quotes)
		{
			if (current[0] != '\0')
				append_to_result(result, current);
			current = ft_strdup("");
			expand_wildcard(result);
		}
		else
		{
			token_char[0] = token[i];
			token_char[1] = '\0';
			append_str(&current, token_char);
		}
	}
	if (current[0] != '\0')
		append_to_result(result, current);
	i = 0;
	return (result);
}

int	handle_redirections(t_list *redir_lst, t_ht *env)
{
	int				fd;
	t_char_arr		*target;
	t_redirection	*redir;
	char			*line;

	while (redir_lst)
	{
		redir = (t_redirection *)redir_lst->content;
		target = expand_text(redir->target, env);
		if (!target || !target->arr || !*target->arr || !**target->arr)
			return (1);
		if (redir->type == T_INPUT)
			fd = open(*target->arr, O_RDONLY);
		else if (redir->type == T_OUTPUT)
			fd = open(*target->arr, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_APPEND)
			fd = open(*target->arr, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == T_HEREDOC)
		{
			unlink(".heredoc");
			fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC);
		}
		if (fd != -1 && (redir->type == T_INPUT || redir->type == T_HEREDOC))
		{
			if (redir->type == T_HEREDOC)
			{
				while (1)
				{
					line = readline("> ");
					if (!line || !ft_strcmp(line, redir->target))
						break ;
					ft_putendl_fd(line, fd);
					free(line);
				}
				close(fd);
				fd = open(".heredoc", O_RDONLY);
			}
			dup2(fd, STDIN_FILENO);
		}
		else if (fd != -1 && (redir->type == T_APPEND || redir->type == T_OUTPUT))
			dup2(fd, STDOUT_FILENO);
		free(target->arr);
		free(target);
		target = NULL;
		if (fd < 0)
			return (1);
		close(fd);
		unlink(".heredoc");
		redir_lst = redir_lst->next;
	}
	return (0);
}

char	*get_lower_cmd(const char *cmd)
{
	size_t	i;
	size_t	len;
	char	*lower_cmd;

	if (!cmd)
		return (NULL);
	len = ft_strlen(cmd);
	lower_cmd = (char *)malloc((len + 1) * sizeof (char));
	if (!lower_cmd)
		return (NULL);
	i = -1;
	while (++i < len)
		lower_cmd[i] = ft_tolower(cmd[i]);
	lower_cmd[i] = '\0';
	return (lower_cmd);
}

bool is_builtin(const char *cmd)
{
	char	*lower_cmd;
	bool	builtin;

	lower_cmd = get_lower_cmd(cmd);
	if (!lower_cmd)
		return (false);
	builtin = (!ft_strcmp(lower_cmd, "echo") || !ft_strcmp(lower_cmd, "cd")
		|| !ft_strcmp(lower_cmd, "pwd") || !ft_strcmp(lower_cmd, "unset")
		|| !ft_strcmp(lower_cmd, "export") || !ft_strcmp(lower_cmd, "env")
		|| !ft_strcmp(lower_cmd, "exit"));
	free(lower_cmd);
	return (builtin);
}

void	exec_non_builtin(t_ast *node, t_ht *env)
{
	size_t		i;
	size_t		j;
	char		*cmd_path;
	t_char_arr	*expanded;
	t_char_arr	*args;

	args = (t_char_arr *)ft_calloc(1, sizeof (t_char_arr));
	expanded = expand_text(node->cmd->name, env);
	if (!expanded || !expanded->size)
		return ;
	cmd_path = build_cmd_path(*(expanded->arr), env);
	if (!cmd_path)
		exit(127);
	i = -1;
	while (++i < expanded->size)
		append_to_result(args, expanded->arr[i]);
	i = 0;
	while (node->cmd->args[++i])
	{
		expanded = expand_text(node->cmd->args[i], env);
		free(node->cmd->args[i]);
		if (!expanded)
			return ;
		j = -1;
		while (++j < expanded->size)
			append_to_result(args, expanded->arr[j]);
	}
	free(node->cmd->args);
	execve(cmd_path, args->arr, ht_to_matrix(env));
	perror("minishell");
	exit(1);
}


int (*get_builtin(char *cmd))(char **, t_ht *)
{
	char	*lower_cmd;

	lower_cmd = get_lower_cmd(cmd);
	if (!lower_cmd)
		return (NULL);
	if (!ft_strcmp(lower_cmd, "echo"))
		return (&ft_echo);
	if (!ft_strcmp(lower_cmd, "pwd"))
		return (&ft_pwd);
	if (!ft_strcmp(lower_cmd, "cd"))
		return (&ft_cd);
	if (!ft_strcmp(lower_cmd, "unset"))
		return (&ft_unset);
	if (!ft_strcmp(lower_cmd, "exit"))
		return (&ft_exit);
	return (NULL);
}

int	exec_builtin(t_ast *node, t_ht *env)
{
	int			saved_stdin;
	int			saved_stdout;
	int			status;
	char		*status_str;
	size_t		i;
	size_t		j;
	t_char_arr	*expanded;
	t_char_arr	*args;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(node->cmd->redirections, env) != 0) 
	{
		perror("minishell");
		return (1);
	}
	args = (t_char_arr *)ft_calloc(1, sizeof (t_char_arr));
	expanded = expand_text(node->cmd->name, env);
	if (!expanded || !expanded->size)
		return (127);
	i = -1;
	while (++i < expanded->size)
		append_to_result(args, expanded->arr[i]);
	i = 0;
	while (node->cmd->args[++i])
	{
		expanded = expand_text(node->cmd->args[i], env);
		free(node->cmd->args[i]);
		if (!expanded)
			return (127);
		j = -1;
		while (++j < expanded->size)
			append_to_result(args, expanded->arr[j]);
	}
	status = (get_builtin(args->arr[0]))(args->arr, env);
	status_str = ft_itoa(status);
	ht_set(env, "?", status_str);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
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
	int		status;
	char	*status_str;

	if (!node)
		return (0);
	if (node->token == T_CMD || node->token == T_NONE)
	{
		status = execute_command(node, env);
		status_str = ft_itoa(status);
		ht_set(env, "?", status_str);
		return (status);
	}
	if (node->token == T_PIPE)
		return (execute_pipe(node, env));
	if (node->token == T_AND)
	{
		status = execute_ast(node->left, env);
		if (status == 0)
			return (execute_ast(node->right, env));
		return (status);
	}
	if (node->token == T_OR)
	{
		status = execute_ast(node->left, env);
		if (status != 0)
			return (execute_ast(node->right, env));
		return (status);
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
