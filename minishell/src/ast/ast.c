#include "minishell.h"

static t_ast	*assign_operator_node(t_ast **root, t_list **token_lst, int indent)
{
	t_list	*it;
	t_ast	*op;

	op = (t_ast *)ft_calloc(1, sizeof (t_ast));
	if (!op)
		return (NULL);
	op->indent = indent;
	op->left = *root;
	op->right = (t_ast *)ft_calloc(1, sizeof (t_ast));
	if (!op->right)
		return (free(op), NULL);
	op->token = ((t_token *)(*token_lst)->content)->type;
	it = *token_lst;
	*token_lst = (*token_lst)->next;
	free(it);
	*root = op;
	return (*root);
}

static t_ast	*ast_add_logical_operator(t_ast **root, t_list **token_lst, int indent)
{
	int	new_op_prec;
	int	root_op_prec;

	if (((t_token *)(*token_lst)->content)->type == T_UNHANDLED
		|| ((!*root || (*root)->token == T_NONE || ((*root)->token != T_CMD
		&& ((*root)->left->token == T_NONE || (*root)->right->token == T_NONE))
		|| !(*token_lst)->next)))
	{
		print_syntax_error(((t_token *)(*token_lst)->content)->value);
		return (NULL);
	}
	new_op_prec = get_precedence(((t_token *)(*token_lst)->content)->type);
	if ((*root)->token != T_CMD)
	{
		root_op_prec = get_precedence((*root)->token);
		if ((*root)->indent <= indent && new_op_prec > root_op_prec)
			return (ast_add_logical_operator(&((*root)->right), token_lst, indent));
	}
	return (assign_operator_node(root, token_lst, indent));
}

static int	are_parentheses_valid(t_ast **ast, t_list **token_lst)
{
	t_token	*token;

	token = ((t_token *)((*token_lst)->next)->content);
	if ((*ast)->token == T_CMD)
	{
		if (!(*ast)->cmd->args[1] && (*token_lst)->next)
			print_syntax_error(token->value);
		else
			print_syntax_error("(");
		return (0);
	}
	return (1);
}

static t_ast	*ast_process_parentheses(t_ast **ast, t_list **token_lst,
	int indent, t_ht *env)
{
	t_ast	*sub_ast;
	t_token	*token;

	if (!are_parentheses_valid(ast, token_lst))
		return (NULL);
	*token_lst = (*token_lst)->next;
	sub_ast = ast_create_from_tokens(token_lst, indent, env);
	if (!(*token_lst) || !sub_ast)
		return (NULL);
	sub_ast->is_subshell = true;
	token = (t_token *)(*token_lst)->content;
	if (*token_lst && token && token->type == T_CLOSE_PARENTHESIS)
		*token_lst = (*token_lst)->next;
	else
		return (NULL);
	if ((*ast)->token == T_NONE)
		*ast = sub_ast;
	else if (!(*ast)->left)
		(*ast)->left = sub_ast;
	else
		(*ast)->right = sub_ast;
	return (sub_ast);
}

t_ast	*ast_create_from_tokens(t_list **token_lst, int indent, t_ht *env)
{
	t_ast	*ast;
	t_token	*token;

	ast = ast_create_root();
	if (!ast)
		return (NULL);
	while (*token_lst)
	{
		token = (t_token *)(*token_lst)->content;
		if (is_word_or_redir(token->type) && !ast_add_cmd(ast, token_lst, env))
			return (NULL);
		else if (is_operation(token->type)
			&& !ast_add_logical_operator(&ast, token_lst, indent))
			return (NULL);
		else if (token->type == T_OPEN_PARENTHESIS
			&& !ast_process_parentheses(&ast, token_lst, indent + 1, env))
			return (NULL);
		else if (token->type == T_CLOSE_PARENTHESIS)
		{
			if (ast->token == T_NONE || !indent)
				return (print_syntax_error(")"), NULL);
			return (ast);
		}
	}
	if (indent != 0)
	{
		print_syntax_error("(");
		return (NULL);
	}
	return (ast);
}
