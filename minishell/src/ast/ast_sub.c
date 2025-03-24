/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:06:36 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:06:38 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_assign_node(t_ast **ast, t_ast *sub_ast)
{
	free(*ast);
	*ast = sub_ast;
}

static void	assign_sub_tree(t_ast **ast, t_ast *sub_ast)
{
	if ((*ast)->token == T_NONE)
		free_assign_node(ast, sub_ast);
	else if (!(*ast)->left)
		free_assign_node(&(*ast)->left, sub_ast);
	else
		free_assign_node(&(*ast)->right, sub_ast);
}

int	ast_process_parentheses(t_ast **ast, t_list **token_lst,
	int indent, t_ht *env)
{
	t_ast	*sub_ast;
	t_token	*token;
	t_list	*it;

	if (!are_parentheses_valid(ast, token_lst))
		return (0);
	it = *token_lst;
	*token_lst = (*token_lst)->next;
	del_token(it->content);
	free(it);
	sub_ast = ast_create_from_tokens(token_lst, indent, env);
	if (!(*token_lst) || !sub_ast)
		return (0);
	sub_ast->is_subshell = true;
	token = (t_token *)(*token_lst)->content;
	if (!(*token_lst && token && token->type == T_CLOSE_PARENTHESIS))
		return (0);
	it = *token_lst;
	*token_lst = (*token_lst)->next;
	del_token(it->content);
	free(it);
	assign_sub_tree(ast, sub_ast);
	return (1);
}
