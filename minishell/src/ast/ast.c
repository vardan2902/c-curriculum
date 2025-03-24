/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:06:52 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:06:54 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_operator_node(t_ast **root, t_list **token_lst,
	int indent)
{
	t_list	*it;
	t_ast	*op;

	op = (t_ast *)ft_calloc(1, sizeof (t_ast));
	if (!op)
		return (0);
	op->indent = indent;
	op->left = *root;
	op->right = (t_ast *)ft_calloc(1, sizeof (t_ast));
	if (!op->right)
		return (free(op), 0);
	op->token = ((t_token *)(*token_lst)->content)->type;
	it = *token_lst;
	*token_lst = (*token_lst)->next;
	free(((t_token *)(it->content))->value);
	free(it->content);
	free(it);
	*root = op;
	return (1);
}

static int	ast_add_logical_operator(t_ast **root, t_list **token_lst,
	int indent)
{
	int	new_op_prec;
	int	root_op_prec;

	if (((t_token *)(*token_lst)->content)->type == T_UNHANDLED
		|| ((!*root || (*root)->token == T_NONE || ((*root)->token != T_CMD
		&& ((*root)->left->token == T_NONE || (*root)->right->token == T_NONE))
		|| !(*token_lst)->next)))
	{
		print_syntax_error(((t_token *)(*token_lst)->content)->value);
		return (0);
	}
	new_op_prec = get_precedence(((t_token *)(*token_lst)->content)->type);
	if ((*root)->token != T_CMD)
	{
		root_op_prec = get_precedence((*root)->token);
		if ((*root)->indent <= indent && new_op_prec > root_op_prec)
			return (ast_add_logical_operator(&((*root)->right), token_lst,
					indent));
	}
	return (assign_operator_node(root, token_lst, indent));
}

static int	process_node(t_ast **ast, t_list **token_lst, int indent, t_ht *env)
{
	t_token	*token;

	token = (t_token *)(*token_lst)->content;
	if (is_word_or_redir(token->type))
		return (ast_add_cmd(ast, token_lst, env));
	else if (is_operation(token->type))
		return (ast_add_logical_operator(ast, token_lst, indent));
	else if (token->type == T_OPEN_PARENTHESIS)
		return (ast_process_parentheses(ast, token_lst, indent + 1, env));
	else if (token->type == T_CLOSE_PARENTHESIS)
	{
		if ((*ast)->token != T_NONE && indent)
			return (2);
		print_syntax_error(")");
		return (0);
	}
	return (0);
}

t_ast	*ast_create_from_tokens(t_list **token_lst, int indent, t_ht *env)
{
	t_ast	*ast;
	int		node_status;

	ast = ast_create_root();
	if (!ast)
		return (NULL);
	while (*token_lst)
	{
		node_status = process_node(&ast, token_lst, indent, env);
		if (node_status == 0)
			return (free_ast_node(&ast));
		else if (node_status == 2)
			return (ast);
	}
	if (indent == 0)
		return (ast);
	free_ast_node(&ast);
	print_syntax_error("(");
	return (NULL);
}
