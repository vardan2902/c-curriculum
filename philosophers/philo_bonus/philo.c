/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:24 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/14 22:20:38 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_think(t_philo *philo)
{
	print_thinking(get_ms_from_start(philo->info->start_time), philo);
}

static void	p_eat(t_philo *philo, t_timeval *tv)
{
	sem_wait(philo->pf->forks);
	print_fork_taken(get_ms_from_start(philo->info->start_time), philo);
	sem_wait(philo->pf->forks);
	print_fork_taken(get_ms_from_start(philo->info->start_time), philo);
	print_eating(get_ms_from_start(philo->info->start_time), philo);
	gettimeofday(tv, NULL);
	philo->last_eat = tv;
	wait_ms(philo->info->time_to_eat);
	sem_post(philo->pf->forks);
	sem_post(philo->pf->forks);
	++philo->eat_count;
	if (philo->eat_count == philo->info->must_eat)
		sem_post(philo->info->eat_count_sem);
}

static void	p_sleep(t_philo *philo)
{
	print_sleeping(get_ms_from_start(philo->info->start_time), philo);
	wait_ms(philo->info->time_to_sleep);
}

void	*start_philo_life(t_philo *philo)
{
	t_timeval		tv;

	if (philo->num % 2 == 0)
		wait_ms(1);
	while (philo)
	{
		p_think(philo);
		p_eat(philo, &tv);
		p_sleep(philo);
	}
	sem_close(philo->pf->forks);
	sem_close(philo->info->eat_count_sem);
	return (NULL);
}
