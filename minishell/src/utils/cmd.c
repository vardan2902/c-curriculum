/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:19:23 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 22:20:00 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_token(t_ast *it, t_token *token,
	t_list **prev_token, t_list **token_lst)
{
	*prev_token = *token_lst;
	if (!it->cmd->name)
		it->cmd->name = token->value;
}

void	init_ct(t_cmd_token *ct, t_token *token)
{
	ct->size = 0;
	ct->prev_token = NULL;
	ct->token = token;
}

void	process_args(t_ast **it, t_list **token_lst,
	t_list *token_it, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
	{
		(*it)->cmd->args[i] = ((t_token *)((*token_lst)->content))->value;
		token_it = *token_lst;
		*token_lst = (*token_lst)->next;
		free(token_it->content);
		free(token_it);
	}
}
