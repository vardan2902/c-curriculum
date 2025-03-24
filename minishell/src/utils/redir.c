/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:49:25 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 15:49:33 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*create_redirection(t_cmd_token_types type)
{
	t_redirection	*redir;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = NULL;
	return (redir);
}

int	is_redir_valid(t_list **token_lst, t_token *token)
{
	if (!*token_lst)
		return (print_syntax_error("newline"), 0);
	if (token->type != T_WORD)
		return (print_syntax_error(token->value), 0);
	return (1);
}
