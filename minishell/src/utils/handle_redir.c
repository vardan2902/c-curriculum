/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:24:03 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 20:27:00 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_cmd *cmd, t_ht *env)
{
	t_list	*redir_lst;

	redir_lst = cmd->redirections;
	while (redir_lst)
	{
		if (handle_redirection(cmd->name,
				(t_redirection *)redir_lst->content, env) != 0)
			return (1);
		redir_lst = redir_lst->next;
	}
	return (0);
}

int	handle_redirections_and_restore(t_cmd *cmd,
	t_ht *env, int saved_stdin, int saved_stdout)
{
	if (handle_redirections(cmd, env) != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	return (0);
}

void	del_redir(void *arg)
{
	t_redirection	*redir;

	redir = (t_redirection *)arg;
	free(redir->target);
	free(redir);
}
