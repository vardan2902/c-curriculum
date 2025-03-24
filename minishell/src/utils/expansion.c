/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:48:05 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 14:49:04 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(const char token, bool *in_single_quotes,
	bool *in_double_quotes)
{
	if (token == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (token == '"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}

t_char_arr	*init_expansion(char **current)
{
	t_char_arr	*result;

	result = ft_calloc(1, sizeof(t_char_arr));
	if (!result)
		return (NULL);
	*current = ft_strdup("");
	if (!*current)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

void	handle_regular_char(char token_char, char **current)
{
	char	str[2];

	str[0] = token_char;
	str[1] = '\0';
	append_str(current, str);
}

int	is_last_space(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
		return (ft_isspace(str[len - 1]));
	return (0);
}

void	init_expand_ctx(t_expand_ctx *ctx, t_char_arr *result,
	char **current)
{
	ctx->result = result;
	ctx->current = current;
	ctx->in_single = false;
	ctx->in_double = false;
	ctx->i = -1;
}
