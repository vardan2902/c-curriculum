/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:46:45 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/27 19:49:43 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_join(char *s1, char *s2);
char	*gnl_strdup(char *s);
char	*gnl_substr(char *s, size_t start, size_t len);
char	*get_next_line(int fd);

#endif
