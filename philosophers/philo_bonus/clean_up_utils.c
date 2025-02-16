/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:07:22 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/16 21:51:28 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_close_opened(t_info *info)
{
	sem_post(info->forks);
	sem_post(info->eat_count_sem);
	sem_post(info->died_sem);
	sem_post(info->finish_sem);
	sem_post(info->print_sem);
	sem_close(info->forks);
	sem_close(info->eat_count_sem);
	sem_close(info->print_sem);
	sem_close(info->died_sem);
	sem_close(info->finish_sem);
}

void	unlink_named_sem(void)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(EAT_COUNT_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DIED_SEM);
	sem_unlink(FINISH_SEM);
}

void	clean_up(t_info *info)
{
	if (info->philos)
		free(info->philos);
	sem_close_opened(info);
	unlink_named_sem();
}
