/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:58:03 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/18 16:02:32 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	init_philos(t_info *info, pid_t philos[200])
{
	int		i;

	sem_unlink(FORKS_SEM);
	info->forks = sem_open(FORKS_SEM, O_CREAT, 0644, info->number_of_philos);
	if (info->forks == SEM_FAILED)
		return ;
	i = -1;
	if (gettimeofday(&info->start_time, NULL) == -1)
		return ;
	while (++i < info->number_of_philos)
	{
		philos[i] = fork();
		if (philos[i] == -1)
		{
			while (i--)
				kill(philos[i], SIGINT);
			exit(0);
		}
		if (!philos[i])
			init_philo(i + 1, info);
	}
}

static void	*finish_check(void *args)
{
	t_info	*info;
	int		i;

	info = (t_info *)args;
	i = info->number_of_philos;
	while (--i >= 0)
		sem_wait(info->eat_count);
	sem_wait(info->print);
	sem_post(info->stop);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	pthread_t	finish_check_thread;

	if (!parse_args(argc, argv, &info))
		return (1);
	init_philos(&info, info.philos);
	if (info.must_eat > 0 && (pthread_create(&finish_check_thread,
				NULL, &finish_check, &info)
			|| pthread_detach(finish_check_thread)))
		return (clean_up(&info), 1);
	sem_wait(info.stop);
	clean_up(&info);
	return (0);
}
