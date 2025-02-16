/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pctrl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:09:50 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/16 22:00:37 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void	alert_finish(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		sem_post(info->finish_sem);
}
*/

void	alert_finish(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
	{
		printf("\n\n\nAAAAAAAA\n\n\n");
		kill(info->philos[i], SIGKILL);
	}
}
