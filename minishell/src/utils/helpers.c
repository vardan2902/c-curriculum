/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:19:57 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 00:24:32 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_strings(char **arr, size_t size)
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

char	*get_prompt_line(void)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(STDIN_FILENO);
	trimmed = ft_strtrim(line, "\n");
	free(line);
	return (trimmed);
}

void	unlink_heredocs(void)
{
	int		i;
	char	*sym;
	char	*heredoc;

	i = 0;
	while (1)
	{
		sym = ft_itoa(i);
		heredoc = ft_strjoin(".heredoc_", sym);
		if (access(heredoc, F_OK) == -1)
			break ;
		free(sym);
		unlink(heredoc);
		free(heredoc);
		++i;
	}
	free(sym);
	free(heredoc);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

int	(*get_builtin(char *cmd))(char **args, t_ht *env)
{
	if (!cmd)
		return (NULL);
	if (!ft_strcmp(cmd, "echo"))
		return (&ft_echo);
	if (!ft_strcmp(cmd, "pwd"))
		return (&ft_pwd);
	if (!ft_strcmp(cmd, "cd"))
		return (&ft_cd);
	if (!ft_strcmp(cmd, "unset"))
		return (&ft_unset);
	if (!ft_strcmp(cmd, "exit"))
		return (&ft_exit);
	if (!ft_strcmp(cmd, "env"))
		return (&ft_env);
	if (!ft_strcmp(cmd, "export"))
		return (&ft_export);
	return (NULL);
}
