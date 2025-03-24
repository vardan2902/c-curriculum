/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:33:38 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 22:53:08 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_first_symbol_invalid(const char *identifier,
	int c, int from_export)
{
	if ((!ft_isalpha(c) && c != '_'))
	{
		if (from_export)
			print_error("minishell: export: `", identifier,
				"': not a valid identifier");
		return (1);
	}
	return (0);
}

static int	is_symbol_invalid(const char *identifier,
	int i, int from_export)
{
	if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
	{
		if (from_export)
		{
			if (identifier[i] == '+' && identifier[i + 1] == '=')
				return (0);
			print_error("minishell: export: `", identifier,
				"': not a valid identifier");
		}
		return (1);
	}
	return (0);
}

int	is_valid_identifier(const char *identifier, int from_export)
{
	int	i;

	i = -1;
	while (identifier[++i])
	{
		if (i == 0 && is_first_symbol_invalid(identifier, identifier[i],
				from_export))
			return (0);
		if (identifier[i] == '=')
			break ;
		if (i != 0 && is_symbol_invalid(identifier, i, from_export))
			return (0);
	}
	return (1);
}

bool	is_builtin(const char *cmd)
{
	bool		builtin;

	builtin = (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
			|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset")
			|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "env")
			|| !ft_strcmp(cmd, "exit"));
	return (builtin);
}

bool	are_parentheses_valid(t_ast **ast, t_list **token_lst)
{
	t_token	*token;

	token = ((t_token *)((*token_lst)->next)->content);
	if ((*ast)->token == T_CMD)
	{
		if (!(*ast)->cmd->args[1] && (*token_lst)->next)
			print_syntax_error(token->value);
		else
			print_syntax_error("(");
		return (false);
	}
	return (true);
}
