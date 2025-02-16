/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:24 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/16 21:47:14 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_state("has taken a fork", philo);
	sem_wait(philo->info->forks);
	print_state("has taken a fork", philo);
	print_state("is eating", philo);
	gettimeofday(&philo->last_eat, NULL);
	wait_ms(philo->info->time_to_eat);
	++philo->eat_count;
	if (philo->eat_count == philo->info->must_eat)
		sem_post(philo->info->eat_count_sem);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void	*died_check(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while ((get_current_ms() - get_ms(&philo->last_eat)) < \
			philo->info->time_to_die)
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

	wait_untill_sim_start(&philo->info->start_time);
	if (gettimeofday(&philo->last_eat, NULL) == -1)
		return (NULL);
	philo->last_eat = philo->info->start_time;
	philo->last_eat.tv_sec += 2;
	if (philo->num % 2)
		wait_ms(1);
	if (pthread_create(&died_check_thread, NULL, &died_check, philo)
		|| pthread_detach(died_check_thread)
		|| pthread_create(&finish_check_thread, NULL, &finish_check, philo)
		|| pthread_detach(finish_check_thread))
		return (NULL);
	while (1)
	{
		print_state("is thinking", philo);
		p_eat(philo);
		print_state("is sleeping", philo);
		wait_ms(philo->info->time_to_sleep);
	}
	return (NULL);
}
