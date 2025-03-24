/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:22:56 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 15:23:04 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_name(void)
{
	char	*heredoc;
	char	*sym;
	int		i;

	i = 0;
	while (1)
	{
		sym = ft_itoa(i);
		heredoc = ft_strjoin(".heredoc_", sym);
		free(sym);
		if (!heredoc)
			return (NULL);
		if (access(heredoc, F_OK) != 0)
			break ;
		free(heredoc);
		++i;
	}
	return (heredoc);
}

static void	process_heredoc_line(t_heredoc_ctx *ctx, char *line, t_ht *env)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (line[++i])
	{
		if (!ctx->contain_quotes && line[i] == '$')
		{
			key = extract_var_name(line, &i);
			if (!key)
				continue ;
			value = ht_get(env, key);
			free(key);
			if (!value)
				continue ;
			ft_putstr_fd(value, ctx->fd);
		}
		else
			ft_putchar_fd(line[i], ctx->fd);
	}
	ft_putchar_fd('\n', ctx->fd);
}

static void	process_heredoc(t_heredoc_ctx *ctx, t_ht *env)
{
	bool	is_not_a_tty;
	char	*line;

	is_not_a_tty = ht_get(env, "#ISNOTATTY");
	while (1)
	{
		if (is_not_a_tty)
			line = get_prompt_line();
		else
			line = readline("> ");
		if (!line)
			break ;
		else if (!ft_strcmp(line, *ctx->target.arr))
		{
			free(line);
			break ;
		}
		process_heredoc_line(ctx, line, env);
		free(line);
	}
}

char	*handle_heredoc(char *delimiter, t_ht *env)
{
	t_heredoc_ctx	ctx;

	ctx.heredoc = get_heredoc_name();
	ctx.fd = open(ctx.heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ctx.target.size = 1;
	ctx.target.arr = (char **)ft_calloc(2, sizeof (char *));
	if (!ctx.target.arr)
		return (NULL);
	ctx.target.arr[0] = ft_strdup(delimiter);
	free(delimiter);
	ctx.contain_quotes = (ft_strchr(*ctx.target.arr, '\'')
			|| ft_strchr(*ctx.target.arr, '"'));
	remove_quotes(&ctx.target);
	process_heredoc(&ctx, env);
	free_char_arr(&ctx.target);
	close(ctx.fd);
	return (ctx.heredoc);
}
