/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:24 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/13 21:00:18 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_live_cycle_routine(void *args)
{
	t_philo			*philo = (t_philo *)args;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_timeval		tv;

	l_fork = &philo->pf->forks[philo->num - 1];
	r_fork = &philo->pf->forks[philo->num % philo->info->number_of_philos];
	if (philo->num % 2 == 0)
		wait_ms(1, philo->info);
	while (philo && !philo->info->philo_died)
	{
		print_thinking(get_ms_from_start(philo->info->start_time), philo);
		pthread_mutex_lock(l_fork);
		print_fork_taken(get_ms_from_start(philo->info->start_time), philo);
		pthread_mutex_lock(r_fork);
		print_fork_taken(get_ms_from_start(philo->info->start_time), philo);
		philo->eating = 1;
		print_eating(get_ms_from_start(philo->info->start_time), philo);
		gettimeofday(&tv, NULL);
		philo->last_eat = &tv;
		wait_ms(philo->info->time_to_eat, philo->info);
		pthread_mutex_unlock(l_fork);
		pthread_mutex_unlock(r_fork);
		philo->eating = 0;
		++philo->eat_count;
		print_sleeping(get_ms_from_start(philo->info->start_time), philo);
		wait_ms(philo->info->time_to_sleep, philo->info);
	}
	return (NULL);
}
