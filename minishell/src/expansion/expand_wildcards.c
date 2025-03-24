/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:57:24 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 00:38:52 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_wildcard_token(const char *token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		if (ft_isquote(token[i]))
		{
			j = i + 1;
			while (token[j] && token[j] != token[i])
				++j;
			i = j;
		}
		else if (token[i] == '*')
			return (1);
		if (token[i])
			++i;
	}
	return (0);
}

static bool	should_skip_entry(int ends_with_slash, struct dirent *entry,
	const char *pattern, struct stat *st)
{
	bool	show_hidden;

	show_hidden = should_show_hidden(pattern);
	if (!show_hidden && ft_strncmp(entry->d_name, ".", 1) == 0)
		return (true);
	if (!match_pattern(pattern, entry->d_name))
		return (true);
	if (ends_with_slash && (stat(entry->d_name, st) == -1
			|| !S_ISDIR(st->st_mode)))
		return (true);
	return (false);
}

static void	add_matches(t_char_arr *matches, const char *pattern,
	int ends_with_slash)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		st;
	char			*name;

	dir = opendir(".");
	if (!dir)
		return ;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (should_skip_entry(ends_with_slash, entry, pattern, &st))
			continue ;
		if (ends_with_slash)
			name = ft_strjoin(entry->d_name, "/");
		else
			name = ft_strdup(entry->d_name);
		append_to_result(matches, name);
	}
	closedir(dir);
}

static void	process_wildcard_token(t_char_arr *new_result, const char *token)
{
	int			ends_with_slash;
	char		*pattern;
	t_char_arr	matches;
	size_t		j;

	pattern = get_pattern(token, &ends_with_slash);
	init_char_arr(&matches);
	add_matches(&matches, pattern, ends_with_slash);
	sort_strings(matches.arr, matches.size);
	if (matches.size == 0)
		append_to_result(new_result, ft_strdup(token));
	else
	{
		j = -1;
		while (++j < matches.size)
			append_to_result(new_result, matches.arr[j]);
		free(matches.arr);
	}
	pattern = ft_free(pattern);
}

void	expand_wildcards(t_char_arr *result)
{
	t_char_arr	new_result;
	size_t		i;
	char		*token;

	init_char_arr(&new_result);
	i = 0;
	while (i < result->size)
	{
		token = result->arr[i];
		if (!is_wildcard_token(token))
			append_to_result(&new_result, ft_strdup(token));
		else
			process_wildcard_token(&new_result, token);
		i++;
	}
	free_char_arr(result);
	*result = new_result;
}
