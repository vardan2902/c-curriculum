/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:47:07 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/28 16:20:29 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*clear_storage(char *storage)
{
	if (storage)
		free(storage);
	return (NULL);
}

static char	*read_line(int fd, char *storage)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		storage = ft_join(storage, buffer);
		if (!storage)
			return (NULL);
	}
	if (bytes_read < 0)
		return (clear_storage(storage));
	return (storage);
}

static char	*extract_line(char *storage)
{
	char	*line;
	size_t	len;

	if (!storage || !*storage)
		return (NULL);
	line = ft_strchr(storage, '\n');
	if (line)
		len = (line - storage) + 1;
	else
		len = ft_strlen(storage);
	return (ft_substr(storage, 0, len));
}

static char	*update_storage(char *storage)
{
	char	*line;
	char	*new_storage;

	line = ft_strchr(storage, '\n');
	if (!line)
		return (clear_storage(storage));
	new_storage = ft_strdup(line + 1);
	free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_line(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	if (!line)
		return (storage = clear_storage(storage));
	storage = update_storage(storage);
	return (line);
}
