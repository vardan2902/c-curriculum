/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:21:20 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 00:23:42 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quoted_pattern(const char **pattern, const char **str)
{
	char	quote;

	quote = **pattern;
	++*pattern;
	while (**pattern != quote)
	{
		if (**pattern == **str)
		{
			++*pattern;
			++*str;
		}
		else
			return (0);
	}
	++*pattern;
	return (1);
}

static int	process_wildcard_pattern(const char **pattern, const char **str)
{
	while (**pattern == '*')
		++*pattern;
	if (!**pattern)
		return (1);
	while (**str)
	{
		if (match_pattern(*pattern, *str))
			return (1);
		++*str;
	}
	return (0);
}

int	match_pattern(const char *pattern, const char *str)
{
	while (*pattern)
	{
		if (ft_isquote(*pattern))
		{
			if (!process_quoted_pattern(&pattern, &str))
				return (0);
		}
		else if (*pattern == '*')
			return (process_wildcard_pattern(&pattern, &str));
		else if (*pattern == *str)
		{
			++pattern;
			++str;
		}
		else
			return (0);
	}
	return (*pattern == '\0' && *str == '\0');
}

char	*get_pattern(const char *token, int *ends_with_slash)
{
	*ends_with_slash = (ft_strlen(token) > 0
			&& token[ft_strlen(token) - 1] == '/');
	if (*ends_with_slash)
		return (ft_substr(token, 0, ft_strlen(token) - 1));
	return (ft_strdup(token));
}

bool	should_show_hidden(const char *pattern)
{
	while (ft_isquote(*pattern))
		++pattern;
	return (*pattern == '.');
}
