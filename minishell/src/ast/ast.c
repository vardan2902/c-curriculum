#include "minishell.h"

static void	ast_add_cmd(t_ast *it, t_list **token_lst)
{
	t_list	*token_it;
	size_t	size;
	size_t	i;
	t_token	*token;

	size = 0;
	i = -1;
	token_it = *token_lst;
	if (it->token == T_NONE)
	{
		token = (t_token *)token_it->content;
		it->cmd = (t_cmd *)malloc(sizeof (t_cmd));
		if (!it->cmd)
			return ;
		it->token = T_CMD;
		it->cmd->name = token->value;
		while (token_it && token && token->type == T_WORD)
		{
			token_it = token_it->next;
			if (token_it && token_it->content)
				token = (t_token *)token_it->content;
			else
				token = NULL;
			++size;
		}
		it->cmd->args = (char **)malloc((size + 1) * sizeof (char *));
		if (!it->cmd->args)
			return (free(it->cmd));
		while (++i < size)
		{
			it->cmd->args[i] = ((t_token *)((*token_lst)->content))->value;
			token_it = *token_lst;
			*token_lst = (*token_lst)->next;
			free(token_it);
		}
		it->cmd->args[size] = NULL;
		return ;
	}
	if (it->right)
		return (ast_add_cmd(it->right, token_lst));
}

static t_ast	*ast_add_logical_operator(t_ast **root, t_list **token_lst)
{
	t_ast	*op;
	t_list	*it;

	if (!*root || (*root)->token == T_NONE || ((*root)->token != T_CMD
		&& ((*root)->left->token == T_NONE || (*root)->right->token == T_NONE))
		|| !(*token_lst)->next)
	{
		print_syntax_error(((t_token *)(*token_lst)->content)->value);
		return (NULL);
	}
	op = (t_ast *)ft_calloc(1, sizeof (t_ast));
	if (!op)
		return (NULL);
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

static t_ast	*ast_create_root(void)
{
	t_ast	*root;

	root = (t_ast *)ft_calloc(1, sizeof (t_ast));
	return (root);
}

static t_ast	*ast_process_parentheses(t_ast **ast, t_list **token_lst, int indent)
{
	t_ast	*sub_ast;
	t_token	*token;

	if ((*ast)->token == T_CMD)
		return (print_syntax_error("("), NULL);
	*token_lst = (*token_lst)->next;
	sub_ast = ast_create_from_tokens(token_lst, indent);
	if (!(*token_lst))
		return (NULL);
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

t_ast	*ast_create_from_tokens(t_list **token_lst, int indent)
{
	t_ast	*ast;
	t_token	*token;

	ast = ast_create_root();
	if (!ast)
		return (NULL);
	while (*token_lst)
	{
		token = (t_token *)(*token_lst)->content;
		if (token->type == T_WORD)
			ast_add_cmd(ast, token_lst);
		else if (token->type == T_OR || token->type == T_AND || token->type == T_PIPE)
		{
			if (!ast_add_logical_operator(&ast, token_lst))
				return (NULL);
		}
		else if (token->type == T_OPEN_PARENTHESIS)
		{
			if (!ast_process_parentheses(&ast, token_lst, indent + 1))
				return (NULL);
		}
		else if (token->type == T_CLOSE_PARENTHESIS)
		{
			if (ast->token == T_NONE || !indent)
				return (print_syntax_error(")"), NULL);
			return (ast);
		}
	}
	return (ast);
}
