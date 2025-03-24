/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:32:22 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 20:35:46 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(expanded->arr);
	free(expanded);
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
	free(expanded->arr);
	free(expanded);
	i = 0;
	while (node->cmd->args[++i])
	{
		if (expand_and_append_args(args, node->cmd->args[i], env,
				ft_strcmp(args->arr[0], "export") == 0))
			return (127);
	}
	return (0);
}

static void	set_env_vars(t_ht *env, t_char_arr *args, int status)
{
	char	*status_str;

	ht_set(env, ft_strdup("_"), ft_strdup(args->arr[args->size - 1]));
	status_str = ft_itoa(status);
	ht_set(env, ft_strdup("?"), status_str);
}

int	free_and_restore(t_char_arr *args, int saved_stdin, int saved_stdout)
{
	free_char_arr(args);
	free(args);
	restore_std_fds(saved_stdin, saved_stdout);
	return (127);
}

int	exec_builtin(t_ast **node, t_ht *env)
{
	int			saved_stdin;
	int			saved_stdout;
	int			status;
	t_char_arr	*args;

	save_std_fds(&saved_stdin, &saved_stdout);
	if (handle_redirections_and_restore((*node)->cmd,
			env, saved_stdin, saved_stdout))
		return (1);
	args = (t_char_arr *)ft_calloc(1, sizeof(t_char_arr));
	if (!args)
		return (1);
	if (process_cmd_args((*node), args, env) != 0)
		return (free_and_restore(args, saved_stdin, saved_stdout));
	ht_set(env, ft_strdup("_"), ft_strdup(args->arr[0]));
	status = (get_builtin(args->arr[0]))(args->arr, env);
	set_env_vars(env, args, status);
	restore_std_fds(saved_stdin, saved_stdout);
	free_char_arr(args);
	free(args);
	return (status);
}
