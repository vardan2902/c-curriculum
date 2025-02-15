/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:58:03 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/14 22:13:33 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_up(t_info *info)
{
	if (info->philos)
		free(info->philos);
	if (info->forks)
		sem_unlink(FORKS_SEM);
	if (info->eat_count_sem)
		sem_unlink(EAT_COUNT_SEM);
	if (info->died_sem)
		sem_unlink(DIED_SEM);
}

static void	init_philo(int num, t_info *info)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof (t_philo));
	if (!philo)
		exit(0);
	philo->num = num;
	philo->info = info;
	philo->eat_count = 0;
	philo->last_eat = info->start_time;
	start_philo_life(philo);
	exit(0);
}

static pid_t	*init_philos(t_info *info)
{
	int		i;
	pid_t	*philos;

	sem_unlink(FORKS_SEM);
	info->forks = sem_open(FORKS_SEM, O_CREAT, 0644, info->number_of_philos);
	i = -1;
	philos = (pid_t *)malloc(info->number_of_philos * sizeof (pid_t));
	if (!philos || gettimeofday(&info->start_time, NULL) == -1)
		return (NULL);
	while (++i < info->number_of_philos)
	{
		philos[i] = fork();
		if (philos[i] == -1)
			return (NULL);
		if (!philos[i])
			init_philo(i + 1, info);
	}
	return (philos);
}

static void	*finish_check(void *args)
{
	t_info	*info;
	int		i;
	
	info = (t_info *)args;
	i = info->number_of_philos;
	while (--i >= 0)
		sem_wait(info->eat_count_sem);
	pkill_all_ctrl(info);
	return (NULL);
}

static void	*died_check(void *args)
{
	t_info	*info;

	info = (t_info *)args;
	sem_wait(info->died_sem);
	pkill_all_ctrl(info);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	pid_t		*philos;
	pthread_t	died_check_thread;
	pthread_t	finish_check_thread;

	if (!parse_args(argc, argv, &info))
		return (1);
	philos = init_philos(&info);
	info.philos = philos;
	if (!philos)
		return (clean_up(&info), 1);
	if (pthread_create(&died_check_thread, NULL, &died_check, &info)
		|| pthread_detach(died_check_thread))
		return (clean_up(&info), 1);
	if (pthread_create(&finish_check_thread, NULL, &finish_check, &info)
		|| pthread_detach(finish_check_thread))
		return (clean_up(&info), 1);
	while (wait(NULL) > 0)
		;
	clean_up(&info);
	return (0);
}
