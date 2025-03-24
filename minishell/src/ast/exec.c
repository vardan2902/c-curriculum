/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:07:44 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:07:46 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_ast_impl(t_ast **root, t_ast **node, t_ht *env)
{
	int		status;

	status = 1;
	if (!node || !*node)
		return (0);
	if ((*node)->token == T_CMD || (*node)->token == T_NONE)
		status = handle_cmd_exec(node, env);
	else if ((*node)->token == T_PIPE)
		status = handle_pipe_exec(root, node, env);
	else if ((*node)->token == T_AND)
		status = handle_and_exec(root, node, env);
	else if ((*node)->token == T_OR)
		status = handle_or_exec(root, node, env);
	free_ast_node(node);
	return (status);
}

static void	exec_subshell(t_ast **root, t_ast **node, t_ht *env)
{
	int	status;

	ht_set(env, ft_strdup("#IS_SUBSHELL"), ft_strdup("TRUE"));
	status = execute_ast_impl(root, node, env);
	ht_clear(env);
	free_ast_node(root);
	exit(status);
}

int	execute_ast(t_ast **root, t_ast **node, t_ht *env)
{
	pid_t	pid;
	int		status;

	if (!node || !*node)
		return (0);
	if ((*node)->is_subshell)
	{
		pid = fork();
		if (pid == 0)
			exec_subshell(root, node, env);
		free_ast_node(node);
		if (pid < 0)
			return (1);
		ignore_signals();
		waitpid(pid, &status, 0);
		setup_signals();
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	status = execute_ast_impl(root, node, env);
	return (status);
}
