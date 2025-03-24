/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:56:40 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 22:57:00 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_node(t_ast **node)
{
	if (node && *node)
		free(*node);
	*node = NULL;
	return (NULL);
}

void	*free_ast_node(t_ast **node)
{
	int		i;

	if (!node || !*node)
		return (NULL);
	if ((*node)->cmd)
	{
		ft_lstclear(&(*node)->cmd->redirections, del_redir);
		i = -1;
		if ((*node)->cmd->args)
		{
			while ((*node)->cmd->args[++i])
				ft_free((*node)->cmd->args[i]);
			ft_free((*node)->cmd->args);
		}
		ft_free((*node)->cmd);
	}
	free_ast_node(&(*node)->left);
	free_ast_node(&(*node)->right);
	return (free_node(node));
}
