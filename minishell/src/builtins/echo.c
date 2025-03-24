/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:41:35 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:41:36 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_flag(char **args)
{
	int	i;
	int	j;
	int	nl_flag;

	nl_flag = -1;
	i = -1;
	while (args[++i])
	{
		j = 0;
		if (args[i][j] != '-' || args[i][j + 1] != 'n')
			break ;
		while (args[i][++j] == 'n')
			continue ;
		if (args[i][j] != '\0')
			break ;
		nl_flag = i;
	}
	return (nl_flag);
}

static void	print_args(char **args, int flag)
{
	int	i;

	i = flag;
	while (args[++i])
	{
		if (i > flag + 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
	}
}

int	ft_echo(char **args, t_ht *env)
{
	int	print_nl;

	(void)env;
	args += 1;
	print_nl = check_for_flag(args);
	print_args(args, print_nl);
	if (print_nl == -1)
		ft_putchar_fd('\n', 1);
	return (0);
}
