#include "minishell.h"

static int ast_add_redirection(t_cmd *cmd, t_list **token_lst, t_list *prev)
{
	t_redirection	*redir;
	t_list			*redir_token;
	t_token			*token;
	t_list			*token_it;

	token = (t_token *)(*token_lst)->content;
	while (*token_lst && (token->type >= T_INPUT && token->type <= T_HEREDOC))
	{
		token = (t_token *)(*token_lst)->content;
		redir = (t_redirection *)malloc(sizeof(t_redirection));
		if (!redir)
			return (0);
		redir->type = token->type;
		token_it = *token_lst;
		*token_lst = (*token_lst)->next;
		if (*token_lst)
			token = (t_token *)(*token_lst)->content;
		free(token_it);
		if (!*token_lst)
			return (print_syntax_error("newline"), free(redir), 0);
		if (token->type != T_WORD)
			return (print_syntax_error(token->value), free(redir), 0);
		redir->target = ((t_token *)(*token_lst)->content)->value;
		token_it = *token_lst;
		*token_lst = (*token_lst)->next;
		free(token_it);
		if (prev)
			prev->next = *token_lst;
		redir_token = ft_lstnew(redir);
		if (!redir_token)
			return (free(redir), 0);
		ft_lstadd_back(&cmd->redirections, redir_token);
	}
	return (1);
}

static int	is_word_or_redir(t_cmd_token_types type)
{
	return (type == T_WORD || (type >= T_INPUT && type <= T_HEREDOC));
}

static int	ast_add_cmd(t_ast *it, t_list **token_lst)
{
	t_list	*token_it;
	t_list	*prev_token;
	size_t	size;
	size_t	i;
	t_token	*token;

	size = 0;
	i = -1;
	token_it = NULL;
	prev_token = NULL;
	if (it->token == T_NONE)
	{
		token = (t_token *)(*token_lst)->content;
		it->cmd = (t_cmd *)ft_calloc(1, sizeof (t_cmd));
		if (!it->cmd)
			return (0);
		while (*token_lst && token && is_word_or_redir(token->type))
		{
			if (token->type >= T_INPUT && token->type <= T_HEREDOC)
			{
				if (!ast_add_redirection(it->cmd, token_lst, prev_token))
					return (0);
			}
			else if (token->type == T_WORD)
			{
				++size;
				if (!token_it)
					token_it = *token_lst;
				prev_token = *token_lst;
				if (it->token == T_NONE)
				{
					it->token = T_CMD;
					it->cmd->name = token->value;
				}
				*token_lst = (*token_lst)->next;
			}
			if (*token_lst && (*token_lst)->content)
				token = (t_token *)(*token_lst)->content;
			else
				token = NULL;
		}
		*token_lst = token_it;
		it->cmd->args = (char **)malloc((size + 1) * sizeof (char *));
		if (!it->cmd->args)
			return (free(it->cmd), 0);
		while (++i < size)
		{
			it->cmd->args[i] = ((t_token *)((*token_lst)->content))->value;
			token_it = *token_lst;
			*token_lst = (*token_lst)->next;
			free(token_it);
		}
		it->cmd->args[size] = NULL;
		return (1);
	}
	if (it->right)
		return (ast_add_cmd(it->right, token_lst));
	return (0);
}

static int get_precedence(int token)
{
	if (token == T_PIPE)
		return 2;
	if (token == T_AND || token == T_OR)
		return 1;
	return 0;
}

static t_ast	*ast_add_logical_operator(t_ast **root, t_list **token_lst)
{
	t_ast	*op;
	t_list	*it;
	int		 new_op_prec;
	int		 root_op_prec;

	if (!*root || (*root)->token == T_NONE || ((*root)->token != T_CMD
		&& ((*root)->left->token == T_NONE || (*root)->right->token == T_NONE))
		|| !(*token_lst)->next)
	{
		print_syntax_error(((t_token *)(*token_lst)->content)->value);
		return (NULL);
	}
	new_op_prec = get_precedence(((t_token *)(*token_lst)->content)->type);
	if ((*root)->token != T_CMD)
	{
		root_op_prec = get_precedence((*root)->token);
		if (new_op_prec > root_op_prec)
			return (ast_add_logical_operator(&((*root)->right), token_lst));
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
	{
		if (!(*ast)->cmd->args[1] && (*token_lst)->next)
			return (print_syntax_error(((t_token *)((*token_lst)->next)->content)->value), NULL);
		return (print_syntax_error("("), NULL);
	}
	*token_lst = (*token_lst)->next;
	sub_ast = ast_create_from_tokens(token_lst, indent);
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
		if ((token->type == T_WORD || (token->type >= T_INPUT && token->type <= T_HEREDOC))
				&& !ast_add_cmd(ast, token_lst))
			return (NULL);
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
