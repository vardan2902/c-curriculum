#include "minishell.h"

void	ast_add_cmd(t_ast *it, t_token_lst **token_lst)
{
	t_token_list	*token_it;
	char			**args;
	size_t			size;
	size_t			i;

	size = 0;
	i = -1;
	token_it = *token_lst;
	if (it->token == NONE)
	{
		it->cmd = (t_cmd *)malloc(sizeof (t_cmd));
		it->token = CMD;
		it->cmd->cmd_name = token_it->token;
		while (token_it && token_it->token_type == WORD)
		{
			token_it = token_it->next;
			++size;
		}
		args = (char **)malloc((size + 1) * sizeof (char *));	
		while (++i < size)
		{
			it->cmd->cmd_args[i] = (*token_lst)->token;
			token_it = *token_lst;
			*token_lst = (*token_lst)->next;
			free(token_it);
		}
		args[size] = NULL;
		it->cmd->cmd_args = args;
		return ;
	}
	if (it->left)
		return (ast_add_cmd(it->left, token_lst));
	if (it->right)
		return (ast_add_cmd(it->right, token_lst));
}

void	ast_add_logical_operator(t_ast **root, t_cmd_token_types type)
{
	t_ast	*op;

	op = (t_ast *)ft_calloc(1, sizeof (t_ast));
	if (!op)
		return ;
	op->left = *root;
	op->right = (t_ast *)ft_calloc(1, sizeof (t_ast));
	if (!op->right)
		return ;
	*root = op;
}

t_ast	*ast_create_root()
{
	t_ast	*root;

	root = (t_ast *)ft_calloc(1, sizeof (t_ast));
	return (root);
}

t_ast	*ast_create_from_tokens(t_token_lst **token_lst)
{
	t_ast		*ast;
	t_ast		*it;

	ast = ast_create_root();
	it = ast;
	while (*token->lst)
	{
		if ((*token_lst)->token_type == CMD)
			ast_add_cmd(ast, token_lst);
		else if ((*token_lst)->token_type == OR || (*token_lst)->token_type == AND)
			ast_add_logical_operator(&ast, token_lst);
		if (!match)	
			(*token_lst) = (*token_lst)->next;
	}
}
