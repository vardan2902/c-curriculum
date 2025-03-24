/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:06:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:06:17 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	process_cmd_tokens(t_ast *it, t_list **token_lst,
	t_list **token_it, t_ht *env)
{
	t_cmd_token	ct;

	*token_it = NULL;
	init_ct(&ct, (t_token *)(*token_lst)->content);
	while (*token_lst && ct.token && is_word_or_redir(ct.token->type))
	{
		ct.type = ct.token->type;
		if (is_redir(ct.type)
			&& !ast_add_redirection(it->cmd, token_lst, ct.prev_token, env))
			return (-1);
		else if (ct.type == T_WORD)
		{
			++ct.size;
			if (!*token_it)
				*token_it = *token_lst;
			update_token(it, ct.token, &ct.prev_token, token_lst);
			*token_lst = (*token_lst)->next;
		}
		if (*token_lst && (*token_lst)->content)
			ct.token = (t_token *)(*token_lst)->content;
		else
			ct.token = NULL;
	}
	return (ct.size);
}

static int	add_cmd(t_ast **it, t_list **token_lst, t_ht *env)
{
	t_list	*token_it;
	ssize_t	size;

	(*it)->token = T_CMD;
	(*it)->cmd = (t_cmd *)ft_calloc(1, sizeof (t_cmd));
	if (!(*it)->cmd)
		return (0);
	size = process_cmd_tokens(*it, token_lst, &token_it, env);
	if (size == -1)
	{
		if (token_it)
			*token_lst = token_it;
		return (0);
	}
	if (size == 0)
		return (1);
	*token_lst = token_it;
	(*it)->cmd->args = (char **)malloc((size + 1) * sizeof (char *));
	if (!(*it)->cmd->args)
		return (free((*it)->cmd), 0);
	process_args(it, token_lst, token_it, size);
	(*it)->cmd->args[size] = NULL;
	return (1);
}

int	ast_add_cmd(t_ast **it, t_list **token_lst, t_ht *env)
{
	if ((*it)->token == T_CMD)
	{
		print_syntax_error(((t_token *)((*token_lst)->content))->value);
		return (0);
	}
	if ((*it)->token == T_NONE)
		return (add_cmd(it, token_lst, env));
	if ((*it)->right)
		return (ast_add_cmd(&(*it)->right, token_lst, env));
	return (0);
}
