/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:34:40 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:34:45 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespaces(char **str)
{
	while (ft_isspace(**str))
		++(*str);
}

void	del_token(void *args)
{
	t_token	*token;

	token = (t_token *)args;
	if (token && token->value)
		free(token->value);
	free(token);
}

t_token	*create_token(char *value, t_cmd_token_types type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof (t_token));
	if (!token)
		return (free(value), NULL);
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*get_operator_token(char **prompt)
{
	if (ft_strncmp(*prompt, "||", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("||"), T_OR));
	if (ft_strncmp(*prompt, "&&", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("&&"), T_AND));
	if (ft_strncmp(*prompt, "<<", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("<<"), T_HEREDOC));
	if (ft_strncmp(*prompt, ">>", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup(">>"), T_APPEND));
	if (**prompt == '|')
		return (++(*prompt), create_token(ft_strdup("|"), T_PIPE));
	if (**prompt == '>')
		return (++(*prompt), create_token(ft_strdup(">"), T_OUTPUT));
	if (**prompt == '<')
		return (++(*prompt), create_token(ft_strdup("<"), T_INPUT));
	if (**prompt == '(')
		return (++(*prompt), create_token(ft_strdup("("), T_OPEN_PARENTHESIS));
	if (**prompt == ')')
		return (++(*prompt), create_token(ft_strdup(")"), T_CLOSE_PARENTHESIS));
	if (**prompt == '&' || **prompt == ';')
		return (++(*prompt), create_token(ft_substr(*prompt - 1, 0, 1),
				T_UNHANDLED));
	return (NULL);
}

size_t	tokenizer_handle_quotes(char **prompt, char quote)
{
	char	*start;

	start = *prompt;
	++(*prompt);
	while (**prompt && **prompt != quote)
		++(*prompt);
	if (**prompt != quote)
		return (0);
	++(*prompt);
	return (*prompt - start);
}
