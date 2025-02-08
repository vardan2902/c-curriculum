/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:45:09 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/08 16:02:04 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_len(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && c != str[len])
		++len;
	return (len);
}

static int	count_words(const char *str, char c)
{
	int	wc;
	int	i;

	i = -1;
	wc = 0;
	while (str[++i])
		if ((i == 0 && c != str[i]) || (i != 0 && c == str[i - 1]
				&& c != str[i]))
			++wc;
	return (wc);
}

static void	free_allocated_memory(char **splitted, int index)
{
	while (index >= 0)
		free(splitted[index--]);
	free(splitted);
}

static char	**allocate_and_fill(char **splitted, const char *s,
	char c, int word_count)
{
	int	i;
	int	j;
	int	word_len;

	i = -1;
	while (++i < word_count)
	{
		while (*s && *s == c)
			++s;
		word_len = get_word_len(s, c);
		splitted[i] = (char *)malloc((word_len + 1) * sizeof(char));
		if (!splitted[i])
		{
			free_allocated_memory(splitted, i - 1);
			return (NULL);
		}
		j = 0;
		while (*s && *s != c)
			splitted[i][j++] = *s++;
		splitted[i][j] = '\0';
	}
	splitted[i] = NULL;
	return (splitted);
}

char	**ft_split(const char *s, char c)
{
	char	**splitted;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	splitted = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	return (allocate_and_fill(splitted, s, c, word_count));
}
