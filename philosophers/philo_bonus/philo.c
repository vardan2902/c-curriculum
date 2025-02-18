/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:24 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/18 17:18:10 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_state("has taken a fork", philo);
	sem_wait(philo->info->forks);
	print_state("has taken a fork", philo);
	sem_wait(philo->meal);
	print_state("is eating", philo);
	gettimeofday(&philo->last_eat, NULL);
	wait_ms(philo->info->time_to_eat);
	++philo->eat_count;
	if (philo->info->must_eat > 0
		&& philo->eat_count == philo->info->must_eat)
		sem_post(philo->info->eat_count);
	sem_post(philo->meal);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void	*died_check(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (usleep(1000) == 0)
	{
		sem_wait(philo->meal);
		if ((get_current_ms() - get_ms(&philo->last_eat)) >= \
				philo->info->time_to_die)
			break ;
		sem_post(philo->meal);
	}
	sem_close(philo->meal);
	print_state("died", philo);
	sem_post(philo->info->stop);
	exit(0);
}

sem_t	get_meal_sem(int num, sem_t **sem)
{
	char	sem_name[14];
	int		i;
	int		tmp;

	sem_name[0] = '/';
	sem_name[1] = 'p';
	tmp = num;
	i = 0;
	if (tmp >= 100)
	{
		sem_name[3 + i++] = '0' + (tmp / 100);
		tmp %= 100;
	}
	if (tmp >= 10 || num >= 100)
	{
		sem_name[3 + i++] = '0' + (tmp / 10);
		tmp %= 10;
	}
	sem_name[3 + i++] = '0' + tmp;
	sem_name[3 + i] = '\0';
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0600, 1);
	if (*sem == SEM_FAILED)
		return (-1);
	return (0);
}

void	*start_philo_life(t_philo *philo)
{
	pthread_t		died_check_thread;

	get_meal_sem(philo->num, &philo->meal);
	philo->info->offset = philo->info->number_of_philos * 80;
	wait_untill_sim_start(&philo->info->start_time, philo->info->offset);
	if (gettimeofday(&philo->last_eat, NULL) == -1)
		return (NULL);
	philo->last_eat = philo->info->start_time;
	philo->last_eat.tv_sec += philo->info->offset / 1000;
	philo->last_eat.tv_usec += (philo->info->offset % 1000) * 1000;
	if (pthread_create(&died_check_thread, NULL, &died_check, philo)
		|| pthread_detach(died_check_thread))
		return (NULL);
	if (philo->num % 2 == 0)
		wait_ms(5);
	while (1)
	{
		print_state("is thinking", philo);
		p_eat(philo);
		print_state("is sleeping", philo);
		wait_ms(philo->info->time_to_sleep);
	}
	return (NULL);
}
