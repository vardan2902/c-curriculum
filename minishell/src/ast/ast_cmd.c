#include "minishell.h"

static void	update_token(t_ast *it, t_token *token,
	t_list **prev_token, t_list **token_lst)
{
	*prev_token = *token_lst;
	if (!it->cmd->name)
		it->cmd->name = token->value;
}

static int	process_cmd_tokens(t_ast *it, t_list **token_lst,
	t_list **token_it, size_t *size)
{
	t_token	*token;
	t_list	*prev_token;

	*token_it = NULL;
	prev_token = NULL;
	token = (t_token *)(*token_lst)->content;
	while (*token_lst && token && is_word_or_redir(token->type))
	{
		if (is_redir(token->type)
			&& !ast_add_redirection(it->cmd, token_lst, prev_token))
			return (0);
		else if (token->type == T_WORD)
		{
			++*size;
			if (!*token_it)
				*token_it = *token_lst;
			update_token(it, token, &prev_token, token_lst);
			*token_lst = (*token_lst)->next;
		}
		if (*token_lst && (*token_lst)->content)
			token = (t_token *)(*token_lst)->content;
		else
			token = NULL;
	}
	return (1);
}

static int	add_cmd(t_ast *it, t_list **token_lst)
{
	t_list	*token_it;
	size_t	size;
	size_t	i;

	size = 0;
	i = -1;
	it->token = T_CMD;
	it->cmd = (t_cmd *)ft_calloc(1, sizeof (t_cmd));
	if (!it->cmd)
		return (0);
	if (!process_cmd_tokens(it, token_lst, &token_it, &size))
		return (0);
	if (size == 0)
		return (1);
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

int	ast_add_cmd(t_ast *it, t_list **token_lst)
{
	if (it->token == T_CMD)
	{
		print_syntax_error(((t_token *)((*token_lst)->content))->value);
		return (0);
	}
	if (it->token == T_NONE)
		return (add_cmd(it, token_lst));
	if (it->right)
		return (ast_add_cmd(it->right, token_lst));
	return (0);
}
