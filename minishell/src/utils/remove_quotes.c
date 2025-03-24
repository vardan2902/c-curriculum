/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:40:54 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 16:40:55 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_rm_quotes_ctx(t_rm_quotes_ctx *ctx)
{
	ctx->j = -1;
	ctx->in_single_quotes = false;
	ctx->in_double_quotes = false;
	ctx->new_len = 0;
}

static void	handle_quotes_for_removal(t_rm_quotes_ctx *ctx, char *token,
	char *new_token)
{
	init_rm_quotes_ctx(ctx);
	while (++ctx->j < ctx->len)
	{
		if (token[ctx->j] == '\'' && !ctx->in_double_quotes)
			ctx->in_single_quotes = !ctx->in_single_quotes;
		else if (token[ctx->j] == '"' && !ctx->in_single_quotes)
			ctx->in_double_quotes = !ctx->in_double_quotes;
		else
			new_token[ctx->new_len++] = token[ctx->j];
	}
}

void	remove_quotes(t_char_arr *result)
{
	char			*token;
	char			*new_token;
	t_rm_quotes_ctx	ctx;

	ctx.i = -1;
	while (++ctx.i < result->size)
	{
		token = result->arr[ctx.i];
		ctx.len = ft_strlen(token);
		new_token = (char *)malloc((ctx.len + 1) * sizeof (char));
		if (!new_token)
			continue ;
		handle_quotes_for_removal(&ctx, token, new_token);
		new_token[ctx.new_len] = '\0';
		ft_free(result->arr[ctx.i]);
		result->arr[ctx.i] = new_token;
	}
}
