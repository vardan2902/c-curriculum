/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:58:37 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 15:51:55 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_redirection_target(t_redirection *redir,
	t_list **token_lst, t_ht *env)
{
	char	*target;
	t_list	*it;

	target = ((t_token *)(*token_lst)->content)->value;
	if (redir->type == T_HEREDOC)
		target = handle_heredoc(target, env);
	redir->target = target;
	it = *token_lst;
	*token_lst = (*token_lst)->next;
	free(it->content);
	free(it);
}

static int	add_redirection_to_cmd(t_cmd *cmd, t_redirection *redir)
{
	t_list	*redir_token;

	redir_token = ft_lstnew(redir);
	if (!redir_token)
	{
		free(redir->target);
		free(redir);
		return (0);
	}
	ft_lstadd_back(&cmd->redirections, redir_token);
	return (1);
}

static int	process_invalid_redirection(t_list *it, t_redirection *redir,
	t_list **token_lst, t_list *prev)
{
	free(((t_token *)it->content)->value);
	free(redir);
	free(it->content);
	free(it);
	if (prev)
		prev->next = *token_lst;
	return (0);
}

static void	next_token_iteration(t_list **token_lst, t_list **token_it,
	t_token **token)
{
	*token_it = *token_lst;
	*token_lst = (*token_lst)->next;
	if (*token_lst)
		*token = (t_token *)(*token_lst)->content;
}

int	ast_add_redirection(t_cmd *cmd, t_list **token_lst, t_list *prev, t_ht *env)
{
	t_redirection	*redir;
	t_token			*token;
	t_list			*it;

	token = (t_token *)(*token_lst)->content;
	while (*token_lst && is_redir(token->type))
	{
		token = (t_token *)(*token_lst)->content;
		redir = create_redirection(token->type);
		if (!redir)
			return (0);
		next_token_iteration(token_lst, &it, &token);
		if (!is_redir_valid(token_lst, token))
			return (process_invalid_redirection(it, redir, token_lst, prev));
		free(((t_token *)it->content)->value);
		process_redirection_target(redir, token_lst, env);
		if (prev)
			prev->next = *token_lst;
		if (!add_redirection_to_cmd(cmd, redir))
			return (0);
		free(it->content);
		free(it);
	}
	return (1);
}
