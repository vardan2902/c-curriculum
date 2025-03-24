/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:07:09 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:07:10 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_first_non_empty(t_char_arr *expanded, t_ast **node, t_ht *env)
{
	while (!expanded)
	{
		expanded = expand_text((*node)->cmd->name, env);
		if (!expanded->arr)
		{
			if (find_last_index((*node)->cmd->args) <= 1)
			{
				free_char_arr(expanded);
				free(expanded);
				return (0);
			}
			free((*node)->cmd->name);
			shift_args(node);
			(*node)->cmd->name = (*node)->cmd->args[0];
			free_char_arr(expanded);
			free(expanded);
			expanded = NULL;
		}
	}
	free_char_arr(expanded);
	free(expanded);
	return (1);
}

int	validate_name(t_ast **node)
{
	t_char_arr	unquoted;
	int			status;

	status = 0;
	unquoted.size = 1;
	unquoted.arr = ft_calloc(2, sizeof(char *));
	unquoted.arr[0] = ft_strdup((*node)->cmd->name);
	remove_quotes(&unquoted);
	if (!ft_strcmp(*unquoted.arr, "."))
	{
		print_error("minishell: .: filename argument required",
			"\n", ".: usage: . filename [arguments]");
		status = 2;
	}
	else if (**unquoted.arr == '\0' || !ft_strcmp(*unquoted.arr, ".."))
	{
		print_error(*unquoted.arr, ": ", "command not found");
		status = 127;
	}
	else if (is_builtin(unquoted.arr[0]))
		status = -2;
	free_char_arr(&unquoted);
	return (status);
}

int	exec_cmd(t_ast **node, t_ht *env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections((*node)->cmd, env))
			exit(1);
		if ((*node)->token == T_CMD)
			exec_non_builtin(node, env);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	ignore_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

int	execute_command(t_ast **node, t_ht *env)
{
	int					status;
	int					last;
	t_char_arr			*expanded;

	expanded = NULL;
	if (!(*node)->cmd->name)
		return (handle_redirections((*node)->cmd, env));
	if (!find_first_non_empty(expanded, node, env))
		return (0);
	status = validate_name(node);
	if (status == -2)
		return (exec_builtin(node, env));
	else if (status != 0)
		return (status);
	last = find_last_index(&(*node)->cmd->args[1]);
	expanded = expand_text((*node)->cmd->args[last], env);
	if (!expanded)
		return (1);
	if (expanded->size > 0)
		ht_set(env, ft_strdup("_"),
			ft_strdup(expanded->arr[expanded->size - 1]));
	free_char_arr(expanded);
	free(expanded);
	return (exec_cmd(node, env));
}
