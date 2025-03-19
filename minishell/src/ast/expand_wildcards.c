#include "minishell.h"

static int	match_pattern(const char *pattern, const char *str)
{
	while (*pattern)
	{
		if (ft_isquote(*pattern))
		{
			char quote = *pattern;
			++pattern;
			while (*pattern != quote)
			{
				if (*pattern == *str)
				{
					++pattern;
					++str;
				}
				else
					return (0);
			}
			++pattern;
		}
		else if (*pattern == '*')
		{
			while (*pattern == '*')
				++pattern;
			if (!*pattern)
				return (1);
			while (*str)
			{
				if (match_pattern(pattern, str))
					return (1);
				++str;
			}
			return (0);
		}
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

static void	sort_strings(char **arr, size_t size)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			++j;
		}
		++i;
	}
}

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

static char	*get_pattern(const char *token, int *ends_with_slash)
{
	*ends_with_slash = (ft_strlen(token) > 0
			&& token[ft_strlen(token) - 1] == '/');
	if (*ends_with_slash)
		return (ft_substr(token, 0, ft_strlen(token) - 1));
	return (ft_strdup(token));
}

static bool	should_show_hidden(const char *pattern)
{
	while (ft_isquote(*pattern))
		++pattern;
	return (*pattern == '.');
}

static void	add_matches(t_char_arr *matches, const char *pattern,
	int ends_with_slash)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		st;
	char			*name;
	bool			show_hidden;

	dir = opendir(".");
	if (!dir)
		return ;
	show_hidden = should_show_hidden(pattern);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if ((!show_hidden && (ft_strncmp(entry->d_name, ".", 1) == 0))
			|| !match_pattern(pattern, entry->d_name)
			|| (ends_with_slash && (stat(entry->d_name, &st) == -1
					|| !S_ISDIR(st.st_mode))))
		{
			entry = readdir(dir);
			continue ;
		}
		if (ends_with_slash)
			name = ft_strjoin(entry->d_name, "/");
		else
			name = ft_strdup(entry->d_name);
		append_to_result(matches, name);
		entry = readdir(dir);
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
	ft_free(pattern);
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
