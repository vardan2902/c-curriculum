/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:07:22 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/18 16:31:40 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_processes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		kill(info->philos[i], SIGINT);
}

static void	sem_close_opened(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		sem_post(info->eat_count);
	sem_close(info->forks);
	sem_close(info->print);
	sem_close(info->eat_count);
	sem_close(info->stop);
}

void	unlink_named_sem(void)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(EAT_COUNT_SEM);
	sem_unlink(STOP_SEM);
}

void	clean_up(t_info *info)
{
	kill_processes(info);
	sem_close_opened(info);
	unlink_named_sem();
}
