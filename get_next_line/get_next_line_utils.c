/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:48:48 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/27 19:48:11 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		++len;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_join(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof (char));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (++i < len1)
		str[i] = s1[i];
	i = -1;
	while (++i < len2)
		str[i + len1] = s2[i];
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)malloc((len + 1) * sizeof (char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[len] = '\0';
	return (sub);
}
