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

static void	clean_up(t_info *info, t_pf *pf, pid_t *philos)
{
	if (philos)
		free(philos);
	if (pf->philos)
		free(pf->philos);
	if (pf->forks)
	{
		sem_unlink(FORKS_SEM);
		sem_close(pf->forks);
	}
	sem_unlink(EAT_COUNT_SEM);
	sem_close(info->eat_count_sem);
}

static void	init_philo(int num, t_info *info, t_pf *pf)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof (t_philo));
	if (!philo)
		exit(0);
	philo->num = num;
	philo->info = info;
	philo->pf = pf;
	philo->eat_count = 0;
	philo->last_eat = &info->start_time;
	if (gettimeofday(philo->last_eat, NULL))
	{
		free(philo);
		exit(0);
	}
	start_philo_life(philo);
	exit(0);
}

static pid_t	*init_philos(t_info *info, t_pf *pf)
{
	int		i;
	pid_t	*philos;

	pf->forks = sem_open(FORKS_SEM, O_CREAT, 0644, info->number_of_philos);
	i = -1;
	philos = (pid_t *)malloc(info->number_of_philos * sizeof (pid_t));
	if (!philos)
		return (NULL);
	while (++i < info->number_of_philos)
	{
		philos[i] = fork();
		if (philos[i] == -1)
			return (NULL);
		if (!philos[i])
			init_philo(i + 1, info, pf);
	}
	return (philos);
}

//static void	*died_check(void *args)
//{
//	t_info	*info;

//	info = (t_info *)args;
//	sem_wait(info->died_sem);
	// KILL PROCESSES
//	return (NULL);
//}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_pf		pf;
	pid_t		*philos;
//	pthread_t	died_check_thread;

	if (!parse_args(argc, argv, &info))
		return (1);
	philos = init_philos(&info, &pf);
	if (!philos)
		return (clean_up(&info, &pf, NULL), 1);
	//	if (pthread_create(&died_check_thread, NULL, &died_check, philos))
//		return (clean_up(&info, &pf, philos), 1);
//	pthread_join(died_check_thread, NULL);
	while (wait(NULL) > 0)
		;
	clean_up(&info, &pf, philos);
	return (0);
}
