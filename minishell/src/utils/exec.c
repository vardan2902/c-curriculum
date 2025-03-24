/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:10 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 18:27:52 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_args(t_ast **node)
{
	int	i;

	i = -1;
	while ((*node)->cmd->args[++i])
		(*node)->cmd->args[i] = (*node)->cmd->args[i + 1];
}

int	find_last_index(char **args)
{
	int	last;

	last = 0;
	while (args[last])
		++last;
	return (last);
}
