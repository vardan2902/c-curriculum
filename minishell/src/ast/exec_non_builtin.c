/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:57:20 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 17:58:49 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_path_or_exit(t_ast **node, t_ht *env,
	t_char_arr *args, t_char_arr *expanded)
{
	size_t	i;
	char	*cmd_path;
	int		status;

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
	return (cmd_path);
}

static void	construct_args(t_ast **node, t_ht *env, t_char_arr *expanded,
	t_char_arr *args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*node)->cmd->args[++i])
	{
		expanded = expand_text((*node)->cmd->args[i], env);
		if (!expanded)
		{
			free_ast_node(node);
			exit(1);
		}
		free((*node)->cmd->args[i]);
		expand_wildcards(expanded);
		remove_quotes(expanded);
		j = -1;
		while (++j < expanded->size)
			append_to_result(args, expanded->arr[j]);
	}
}

void	exec_non_builtin(t_ast **node, t_ht *env)
{
	size_t		i;
	char		*cmd_path;
	t_char_arr	*expanded;
	t_char_arr	*args;

	args = (t_char_arr *)ft_calloc(1, sizeof (t_char_arr));
	expanded = expand_text((*node)->cmd->name, env);
	if (!expanded || !expanded->size)
		return ;
	expand_wildcards(expanded);
	remove_quotes(expanded);
	cmd_path = get_cmd_path_or_exit(node, env, args, expanded);
	i = -1;
	while (++i < expanded->size)
		append_to_result(args, expanded->arr[i]);
	construct_args(node, env, expanded, args);
	free((*node)->cmd->args);
	execve(cmd_path, args->arr, ht_to_matrix(env));
	perror("minishell");
	exit(1);
}
