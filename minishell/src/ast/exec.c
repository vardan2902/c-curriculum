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
			return (print_error("minishell: ", cmd, ": No such file or directory"), NULL);
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
	print_error("minishell: ", cmd, ": command not found");
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

static void init_char_arr(t_char_arr *arr)
{
	arr->arr = NULL;
	arr->size = 0;
}

static void free_char_arr(t_char_arr *arr)
{
	size_t i;

	i = 0;
	while (i < arr->size)
		free(arr->arr[i++]);
	free(arr->arr);
	arr->arr = NULL;
	arr->size = 0;
}

static int is_quoted(const char *token)
{
	size_t len;
	char first;

	if (!token)
		return (0);
	len = ft_strlen(token);
	if (len < 2)
		return (0);
	first = token[0];
	return ((first == '\'' || first == '"') && token[len - 1] == first);
}

static int match_pattern(const char *pattern, const char *str)
{
	while (*pattern && *str) {
		if (*pattern == '*') {
			while (*pattern == '*')
				++pattern;
			if (!*pattern)
				return (1);
			while (*str) {
				if (match_pattern(pattern, str))
					return (1);
				++str;
			}
			return (0);
		} else if (*pattern == *str) {
			++pattern;
			++str;
		} else {
			return (0);
		}
	}
	return (*pattern == '\0' && *str == '\0');
}

static void	sort_strings(char **arr, size_t size)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			++j;
		}
		++i;
	}
}

void	expand_wildcards(t_char_arr *result)
{
	t_char_arr		new_result;
	size_t			i;
	char			*token;
	DIR				*dir;
	struct dirent	*entry;
	t_char_arr		matches;

	init_char_arr(&new_result);
	i = 0;
	while (i < result->size)
	{
		token = result->arr[i];
		if (is_quoted(token) || !ft_strchr(token, '*'))
		{
			append_to_result(&new_result, ft_strdup(token));
			++i;
			continue ;
		}
		int ends_with_slash = (ft_strlen(token) > 0 && token[ft_strlen(token) - 1] == '/');
		char *pattern;
		if (ends_with_slash)
			pattern = ft_substr(token, 0, ft_strlen(token) - 1);
		else
			pattern = ft_strdup(token);
		dir = opendir(".");
		if (!dir) {
			append_to_result(&new_result, ft_strdup(token));
			ft_free(pattern);
			i++;
			continue;
		}
		init_char_arr(&matches);
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
				continue ;
			if (!match_pattern(pattern, entry->d_name))
				continue ;
			struct stat st;
			if (ends_with_slash && (stat(entry->d_name, &st) == -1 || !S_ISDIR(st.st_mode)))
				continue;
			char *name;
			if (ends_with_slash)
				name = ft_strjoin(entry->d_name, "/");
			else
				name = ft_strdup(entry->d_name);
			append_to_result(&matches, name);
		}
		closedir(dir);
		ft_free(pattern);
		sort_strings(matches.arr, matches.size);
		if (matches.size == 0)
			append_to_result(&new_result, ft_strdup(token));
		else {
			size_t j = 0;
			while (j < matches.size)
				append_to_result(&new_result, matches.arr[j++]);
			free(matches.arr);
		}
		i++;
	}
	free_char_arr(result);
	*result = new_result;
}

static void handle_quotes(const char token, bool *in_single_quotes, bool *in_double_quotes)
{
	if (token == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (token == '"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
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
		handle_quotes(token[i], &in_single_quotes, &in_double_quotes);
		if (!token[i])
			break ;
		if (token[i] == '$' && !in_single_quotes)
		{
			if (!token[i + 1] || ft_isspace(token[i + 1]))
			{
				token_char[0] = token[i];
				token_char[1] = '\0';
				append_str(&current, token_char);
				continue ;
			}
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
			continue ;
		}
		else if (token[i] == '~' && (token[i + 1] == '/' || token[i + 1] == '\0'))
		{
			if (i == 0)
			{
				free(current);
				current = ft_strdup(ht_get(env, "HOME"));
				continue ;
			}
			else if (token[i - 1] == '=')
			{
				char *identifier = ft_substr(current, 0, ft_strlen(current) - 1);
				if (is_valid_identifier(identifier, 0))
					append_str(&current, ht_get(env, "HOME"));
				else
					append_str(&current, "~");
				free(identifier);
				continue ;
			}
		}
		token_char[0] = token[i];
		token_char[1] = '\0';
		append_str(&current, token_char);
	}
	if (current[0] != '\0')
		append_to_result(result, current);
	i = 0;
	return (result);
}

void remove_quotes(t_char_arr *result)
{
	size_t i;
	size_t j;
	char *token;
	char *new_token;
	size_t len;
	int in_single_quotes;
	int in_double_quotes;

	i = 0;
	while (i < result->size)
	{
		token = result->arr[i];
		len = ft_strlen(token);
		new_token = (char *)malloc((len + 1) * sizeof (char));
		if (!new_token)
			continue ;
		j = 0;
		in_single_quotes = 0;
		in_double_quotes = 0;
		size_t new_len = 0;

		while (j < len)
		{
			if (token[j] == '\'' && !in_double_quotes)
			{
				in_single_quotes = !in_single_quotes;
				j++;
			}
			else if (token[j] == '"' && !in_single_quotes)
			{
				in_double_quotes = !in_double_quotes;
				j++;
			}
			else
				new_token[new_len++] = token[j++];
		}
		new_token[new_len] = '\0';
		ft_free(result->arr[i]);
		result->arr[i] = new_token;
		i++;
	}
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
	char		*lower_cmd;
	bool		builtin;
	t_char_arr	expanded;

	lower_cmd = ft_strdup(cmd);
	init_char_arr(&expanded);
	expanded.size = 1;
	expanded.arr = &lower_cmd;
	remove_quotes(&expanded);
	lower_cmd = get_lower_cmd(*expanded.arr);
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
	expand_wildcards(expanded);
	remove_quotes(expanded);
	cmd_path = build_cmd_path(*(expanded->arr), env);
	if (!cmd_path)
		exit(127);
	ht_set(env, "_", cmd_path);
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
		expand_wildcards(expanded);
		remove_quotes(expanded);
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
	if (!ft_strcmp(lower_cmd, "env"))
		return (&ft_env);
	if (!ft_strcmp(lower_cmd, "export"))
		return (&ft_export);
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
	expand_wildcards(expanded);
	remove_quotes(expanded);
	i = -1;
	while (++i < expanded->size)
		append_to_result(args, expanded->arr[i]);
	i = 0;
	while (node->cmd->args[++i])
	{
		expanded = expand_text(node->cmd->args[i], env);
		if (ft_strcmp(get_lower_cmd(args->arr[0]), "export"))
			expand_wildcards(expanded);
		remove_quotes(expanded);
		free(node->cmd->args[i]);
		if (!expanded)
			return (127);
		j = -1;
		while (++j < expanded->size)
			append_to_result(args, expanded->arr[j]);
	}
	ht_set(env, "_", args->arr[0]);
	status = (get_builtin(args->arr[0]))(args->arr, env);
	ht_set(env, "_", args->arr[args->size - 1]);
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
	pid_t				pid;
	int					status;
	int					last;
	t_char_arr			*expanded;
	struct sigaction	sa;

	if (is_builtin(node->cmd->name)) 
		return (exec_builtin(node, env));
	last = 0;
	while (node->cmd->args[last])
		++last;
	--last;
	expanded = expand_text(node->cmd->args[last], env);
	if (!expanded)
		return (1);
	ht_set(env, "_", expanded->arr[expanded->size - 1]);
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
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL); 
		sigaction(SIGQUIT, &sa, NULL); 
		waitpid(pid, &status, 0);
		setup_signals();
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
	int					pipefd[2];
	pid_t				left_pid;
	pid_t				right_pid;
	int					left_status;
	int					right_status;
	struct sigaction	sa;

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
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL); 
	sigaction(SIGQUIT, &sa, NULL); 
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
	setup_signals();
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
	pid_t   			pid;
	int	 				status;
	struct sigaction	sa;

	if (!node)
		return (0);
	if (node->is_subshell)
	{
		pid = fork();
		if (pid == 0)
		{
			ht_set(env, "#IS_SUBSHELL", "TRUE");
			status = execute_ast_impl(node, env);
			exit(status);
		}
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		waitpid(pid, &status, 0);
		setup_signals();
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	return (execute_ast_impl(node, env));
}
