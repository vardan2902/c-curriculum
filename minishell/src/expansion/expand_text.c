/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:40:08 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 14:48:34 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_tilde_expansion(const char *token, int i,
	char **current, t_ht *env)
{
	char	*identifier;
	char	*home;

	home = ht_get(env, "HOME");
	if (!home)
		return ;
	if (i == 0)
	{
		free(*current);
		*current = ft_strdup(home);
	}
	else if (i > 0 && token[i - 1] == '=')
	{
		identifier = ft_substr(*current, 0, ft_strlen(*current) - 1);
		if (is_valid_identifier(identifier, 0))
			append_str(current, home);
		else
			append_str(current, "~");
		free(identifier);
	}
}

static void	expand_variable(t_expand_ctx *ctx,	const char *token, t_ht *env)
{
	char	*key;
	char	*value;
	char	str[2];

	if (!token[ctx->i + 1] || (!ft_isalnum(token[ctx->i + 1])
			&& !ft_strchr("_?\"'", token[ctx->i + 1]))
		|| (ctx->in_double && ft_isquote(token[ctx->i + 1])))
	{
		str[0] = token[ctx->i];
		str[1] = '\0';
		append_str(ctx->current, str);
		return ;
	}
	key = extract_var_name(token, &ctx->i);
	if (!key)
		return ;
	value = ht_get(env, key);
	free (key);
	if (!value)
		return ;
	append_str(ctx->current, value);
	if (!ctx->in_double)
		split_and_update(ctx->current, ctx->result, is_last_space(value));
	return ;
}

static void	expand_symbols(const char *token, char **current,
	t_char_arr *result, t_ht *env)
{
	t_expand_ctx	ctx;

	init_expand_ctx(&ctx, result, current);
	while (token && token[++ctx.i])
	{
		handle_quotes(token[ctx.i], &ctx.in_single, &ctx.in_double);
		if (!token[ctx.i])
			break ;
		if (token[ctx.i] == '$' && !ctx.in_single)
			expand_variable(&ctx, token, env);
		else if (token[ctx.i] == '~'
			&& (token[ctx.i + 1] == '/' || !token[ctx.i + 1]))
			handle_tilde_expansion(token, ctx.i, ctx.current, env);
		else
			handle_regular_char(token[ctx.i], ctx.current);
	}
}

t_char_arr	*expand_text(const char *token, t_ht *env)
{
	t_char_arr	*result;
	char		*current;

	result = init_expansion(&current);
	if (!result)
		return (NULL);
	expand_symbols(token, &current, result, env);
	if (current[0] != '\0')
		append_to_result(result, current);
	else
		free(current);
	return (result);
}
