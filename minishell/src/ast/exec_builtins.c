#include "minishell.h"

static int	(*get_builtin(char *cmd))(char **args, t_ht *env)
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

static int	expand_and_append_args(t_char_arr *args, char *arg,
	t_ht *env, int is_export)
{
	t_char_arr	*expanded;
	size_t		j;

	expanded = expand_text(arg, env);
	if (!expanded)
		return (127);
	if (!is_export)
		expand_wildcards(expanded);
	remove_quotes(expanded);
	j = -1;
	while (++j < expanded->size)
		append_to_result(args, expanded->arr[j]);
	return (0);
}

static int	process_cmd_args(t_ast *node, t_char_arr *args, t_ht *env)
{
	t_char_arr	*expanded;
	size_t		i;

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
		if (expand_and_append_args(args, node->cmd->args[i], env,
				ft_strcmp(get_lower_cmd(args->arr[0]), "export") == 0))
			return (127);
	}
	return (0);
}

static void	set_env_vars(t_ht *env, t_char_arr *args, int status)
{
	char	*status_str;

	ht_set(env, "_", args->arr[args->size - 1]);
	status_str = ft_itoa(status);
	ht_set(env, "?", status_str);
}

int	exec_builtin(t_ast *node, t_ht *env)
{
	int			saved_stdin;
	int			saved_stdout;
	int			status;
	t_char_arr	*args;

	save_std_fds(&saved_stdin, &saved_stdout);
	if (handle_redirections_and_restore(node->cmd->redirections,
			env, saved_stdin, saved_stdout))
		return (1);
	args = (t_char_arr *)ft_calloc(1, sizeof(t_char_arr));
	if (!args)
		return (1);
	if (process_cmd_args(node, args, env) != 0)
	{
		free(args);
		restore_std_fds(saved_stdin, saved_stdout);
		return (127);
	}
	ht_set(env, "_", args->arr[0]);
	status = (get_builtin(args->arr[0]))(args->arr, env);
	set_env_vars(env, args, status);
	restore_std_fds(saved_stdin, saved_stdout);
	free(args);
	return (status);
}
