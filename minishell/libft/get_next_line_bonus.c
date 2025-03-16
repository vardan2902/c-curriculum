/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:47:07 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/28 16:24:55 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	while (!gnl_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		storage = gnl_join(storage, buffer);
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
	line = gnl_strchr(storage, '\n');
	if (line)
		len = (line - storage) + 1;
	else
		len = gnl_strlen(storage);
	return (gnl_substr(storage, 0, len));
}

static char	*update_storage(char *storage)
{
	char	*line;
	char	*new_storage;

	line = gnl_strchr(storage, '\n');
	if (!line)
		return (clear_storage(storage));
	new_storage = gnl_strdup(line + 1);
	free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[FOPEN_MAX + 1];
	char		*line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	storage[fd] = read_line(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = extract_line(storage[fd]);
	if (!line)
		return (storage[fd] = clear_storage(storage[fd]));
	storage[fd] = update_storage(storage[fd]);
	return (line);
}
