/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:24 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/14 19:49:43 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_think(t_philo *philo)
{
	print_state("is thinking", philo);
}

static void	p_eat(t_philo *philo, pthread_mutex_t *l_fork,
	pthread_mutex_t *r_fork, t_timeval *tv)
{
	pthread_mutex_lock(l_fork);
	print_state("has taken a fork", philo);
	pthread_mutex_lock(r_fork);
	print_state("has taken a fork", philo);
	print_state("is eating", philo);
	gettimeofday(tv, NULL);
	philo->last_eat = tv;
	wait_ms(philo->info->time_to_eat, philo->info);
	pthread_mutex_unlock(l_fork);
	pthread_mutex_unlock(r_fork);
	++philo->eat_count;
	if (philo->eat_count == philo->info->must_eat)
	{
		pthread_mutex_lock(&philo->info->eat_count_mutex);
		++philo->info->total_ate;
		pthread_mutex_unlock(&philo->info->eat_count_mutex);
	}
}

static void	p_sleep(t_philo *philo)
{
	print_state("is sleeping", philo);
	wait_ms(philo->info->time_to_sleep, philo->info);
}

void	*philo_routine(void *args)
{
	t_timeval		tv;
	t_philo			*philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	philo = (t_philo *)args;
	l_fork = &philo->pf->forks[philo->num - 1];
	r_fork = &philo->pf->forks[philo->num % philo->info->number_of_philos];
	if (philo->num % 2 == 0)
		wait_ms(1, philo->info);
	while (philo && !philo->info->finished)
	{
		p_think(philo);
		p_eat(philo, l_fork, r_fork, &tv);
		p_sleep(philo);
	}
	return (NULL);
}
