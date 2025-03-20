#include "minishell.h"

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
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

void	exec_non_builtin(t_ast *node, t_ht *env)
{
	size_t		i;
	size_t		j;
	char		*cmd_path;
	t_char_arr	*expanded;
	t_char_arr	*args;
	int			status;

	args = (t_char_arr *)ft_calloc(1, sizeof (t_char_arr));
	expanded = expand_text(node->cmd->name, env);
	if (!expanded || !expanded->size)
		return ;
	expand_wildcards(expanded);
	remove_quotes(expanded);
	cmd_path = build_cmd_path(*(expanded->arr), env, &status);
	if (!cmd_path)
	{
		free_ast_node(node);
		free(args);
		i = -1;
		while (++i < expanded->size)
			free(expanded->arr[i]);
		free(expanded->arr);
		free(expanded);
		exit(status);
	}
	ht_set(env, ft_strdup("_"), cmd_path);
	i = -1;
	while (++i < expanded->size)
		append_to_result(args, expanded->arr[i]);
	i = 0;
	while (node->cmd->args[++i])
	{
		expanded = expand_text(node->cmd->args[i], env);
		if (!expanded)
		{
			free_ast_node(node);
			exit(1);
		}
		free(node->cmd->args[i]);
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

int	execute_command(t_ast *node, t_ht *env)
{
	pid_t				pid;
	int					status;
	int					last;
	t_char_arr			*expanded;
	struct sigaction	sa;

	expanded = NULL;
	if (!node->cmd->name)
		return (handle_redirections(node->cmd, env));
	while (!expanded)
	{
		expanded = expand_text(node->cmd->name, env);
		if (!expanded->arr)
		{
			last = 0;
			while (node->cmd->args[last])
				++last;
			if (last <= 1)
				return (0);
			free(node->cmd->name);
			int i = -1;
			while (node->cmd->args[++i])
				node->cmd->args[i] = node->cmd->args[i + 1];
			node->cmd->name = node->cmd->args[0];
		}
	}
	t_char_arr	unquoted;

	unquoted.size = 1;
	unquoted.arr = ft_calloc(2, sizeof(char *));
	unquoted.arr[0] = ft_strdup(node->cmd->name);
	remove_quotes(&unquoted);
	if (!ft_strcmp(*unquoted.arr, "."))
	{
		print_error("minishell: .: filename argument required",
			"\n", ".: usage: . filename [arguments]");
		return (2);
	}
	if (**unquoted.arr == '\0' || !ft_strcmp(*unquoted.arr, ".."))
	{
		print_error(*unquoted.arr, ": ", "command not found");
		return (127);
	}

	if (is_builtin(unquoted.arr[0]))
	{
		free_char_arr(&unquoted);
		return (exec_builtin(node, env));
	}
	free_char_arr(&unquoted);
	last = 0;
	while (node->cmd->args[last + 1])
		++last;
	free_char_arr(expanded);
	free(expanded);
	expanded = expand_text(node->cmd->args[last], env);
	if (!expanded)
		return (1);
	if (expanded->size > 0)
		ht_set(env, ft_strdup("_"), ft_strdup(expanded->arr[expanded->size - 1]));
	free_char_arr(expanded);
	free(expanded);
	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(node->cmd, env))
			exit(1);
		if (node->token == T_CMD)
			exec_non_builtin(node, env);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	else
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;		 
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
		ht_set(env, ft_strdup("?"), status_str);
		free_ast_node(node);
		return (status);
	}
	if (node->token == T_PIPE)
	{
		status = execute_pipe(node, env);
		status_str = ft_itoa(status);
		free_ast_node(node);
		return (status);
	}
	if (node->token == T_AND)
	{
		status = execute_ast(node->left, env);
		if (status == 0)
			status = execute_ast(node->right, env);
		free_ast_node(node);
		return (status);
	}
	if (node->token == T_OR)
	{
		status = execute_ast(node->left, env);
		if (status != 0)
			status = execute_ast(node->right, env);
		free_ast_node(node);
		return (status);
	}
	return (1);
}

void	del_redir(void *arg)
{
	t_redirection	*redir;

	redir = (t_redirection *)arg;
	free(redir->target);
	free(redir);
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
			ht_set(env, ft_strdup("#IS_SUBSHELL"), ft_strdup("TRUE"));
			status = execute_ast_impl(node, env);
			exit(status);
		}
		if (pid < 0)
			return (1);
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		waitpid(pid, &status, 0);
		setup_signals();
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	status = execute_ast_impl(node, env);
	return (status);
}
