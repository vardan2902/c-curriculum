/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:06:45 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:06:47 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_precedence(int token)
{
	if (token == T_PIPE)
		return (2);
	if (token == T_AND || token == T_OR)
		return (1);
	return (0);
}

t_ast	*ast_create_root(void)
{
	t_ast	*root;

	root = (t_ast *)ft_calloc(1, sizeof (t_ast));
	return (root);
}

bool	is_redir(t_cmd_token_types type)
{
	return (type >= T_INPUT && type <= T_HEREDOC);
}

bool	is_word_or_redir(t_cmd_token_types type)
{
	return (type == T_WORD || is_redir(type));
}

bool	is_operation(t_cmd_token_types type)
{
	return (type == T_OR || type == T_AND
		|| type == T_PIPE || type == T_UNHANDLED);
}
