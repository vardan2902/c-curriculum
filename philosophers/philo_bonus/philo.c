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
	print_thinking(philo);
}

static void	p_eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_fork_taken(philo);
	sem_wait(philo->info->forks);
	print_fork_taken(philo);
	print_eating(philo);
	gettimeofday(&philo->last_eat, NULL);
	wait_ms(philo->info->time_to_eat);
	++philo->eat_count;
	if (philo->eat_count == philo->info->must_eat)
		sem_post(philo->info->eat_count_sem);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void	p_sleep(t_philo *philo)
{
	print_sleeping(philo);
	wait_ms(philo->info->time_to_sleep);
}

static void	*died_check(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	while ((get_current_ms() - get_ms(&philo->last_eat)) < philo->info->time_to_die)
		usleep(5000);
	sem_post(philo->info->died_sem);
	print_died(philo);
	return (NULL);
}

void	*start_philo_life(t_philo *philo)
{
	pthread_t		died_check_thread;

	if (pthread_create(&died_check_thread, NULL, &died_check, philo)
		|| pthread_detach(died_check_thread))
		return (NULL);
	if (philo->num % 2 == 0)
		wait_ms(60);
	while (1)
	{
		p_think(philo);
		p_eat(philo);
		p_sleep(philo);
	}
	return (NULL);
}
