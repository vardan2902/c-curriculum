/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:41:38 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:42:05 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_ht *env)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	if (i > 1)
	{
		print_error("env: ", "", "invalid arguments");
		return (1);
	}
	print_env(env, 0);
	return (0);
}
