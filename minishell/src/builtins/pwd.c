/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:42:25 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:42:26 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_ht *env)
{
	char	cwd[PATH_MAX];

	(void)args;
	(void)env;
	if (getcwd(cwd, sizeof (cwd)) != NULL)
		ft_putendl_fd(cwd, 1);
	else
		perror("minishell: pwd");
	return (0);
}
