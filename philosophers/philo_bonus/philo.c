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
	print_state("is thinking", philo);
}

static void	p_eat(t_philo *philo)
{
	sem_wait(philo->info->fork_guard_sem);
		sem_wait(philo->info->forks);
		print_state("has taken a fork", philo);
		sem_wait(philo->info->forks);
		print_state("has taken a fork", philo);
	sem_post(philo->info->fork_guard_sem);
	print_state("is eating", philo);
	++philo->eat_count;
	if (philo->eat_count == philo->info->must_eat)
		sem_post(philo->info->eat_count_sem);
	gettimeofday(&philo->last_eat, NULL);
	wait_ms(philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void	p_sleep(t_philo *philo)
{
	print_state("is sleeping", philo);
	wait_ms(philo->info->time_to_sleep);
}

static void	*died_check(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	while ((get_current_ms() - get_ms(&philo->last_eat)) < philo->info->time_to_die)
		usleep(5000);
	print_state("died", philo);
	sem_post(philo->info->died_sem);
	sem_close_opened(philo->info);
	exit(0);
}

static void	*finish_check(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	sem_wait(philo->info->finish_sem);
	sem_close_opened(philo->info);
	exit(0);
}

void	*start_philo_life(t_philo *philo)
{
	pthread_t		died_check_thread;
	pthread_t		finish_check_thread;

	if (pthread_create(&died_check_thread, NULL, &died_check, philo)
		|| pthread_detach(died_check_thread) || 
		pthread_create(&finish_check_thread, NULL, &finish_check, philo)
		|| pthread_detach(finish_check_thread))
		return (NULL);
	while (1)
	{
		p_think(philo);
		p_eat(philo);
		p_sleep(philo);
	}
	return (NULL);
}
