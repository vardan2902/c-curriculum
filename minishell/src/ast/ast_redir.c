#include "minishell.h"

static t_redirection	*create_redirection(t_cmd_token_types type)
{
	t_redirection	*redir;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = NULL;
	return (redir);
}

static int	is_redir_valid(t_list **token_lst, t_token *token)
{
	if (!*token_lst)
		return (print_syntax_error("newline"), 0);
	if (token->type != T_WORD)
		return (print_syntax_error(token->value), 0);
	return (1);
}

static void	process_redirection_target(t_redirection *redir, t_list **token_lst)
{
	t_list	*token_it;

	redir->target = ((t_token *)(*token_lst)->content)->value;
	token_it = *token_lst;
	*token_lst = (*token_lst)->next;
	free(token_it);
}

static int	add_redirection_to_cmd(t_cmd *cmd, t_redirection *redir)
{
	t_list	*redir_token;

	redir_token = ft_lstnew(redir);
	if (!redir_token)
	{
		free(redir);
		return (0);
	}
	ft_lstadd_back(&cmd->redirections, redir_token);
	return (1);
}

int	ast_add_redirection(t_cmd *cmd, t_list **token_lst, t_list *prev)
{
	t_redirection	*redir;
	t_token			*token;
	t_list			*token_it;

	token = (t_token *)(*token_lst)->content;
	while (*token_lst && is_redir(token->type))
	{
		token = (t_token *)(*token_lst)->content;
		redir = create_redirection(token->type);
		if (!redir)
			return (0);
		token_it = *token_lst;
		*token_lst = (*token_lst)->next;
		free(token_it);
		if (*token_lst)
			token = (t_token *)(*token_lst)->content;
		if (!is_redir_valid(token_lst, token))
			return (free(redir), 0);
		process_redirection_target(redir, token_lst);
		if (prev)
			prev->next = *token_lst;
		if (!add_redirection_to_cmd(cmd, redir))
			return (0);
	}
	return (1);
}
