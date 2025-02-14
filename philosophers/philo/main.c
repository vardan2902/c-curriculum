/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:58:03 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/14 20:04:00 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_up(t_info *info, t_pf *pf, t_philo **philos)
{
	int	i;

	if (pf->philos)
		free(pf->philos);
	if (pf->forks)
	{
		i = -1;
		while (++i < info->number_of_philos)
			pthread_mutex_destroy(&pf->forks[i]);
		free(pf->forks);
	}
	if (philos)
	{
		i = -1;
		while (++i < info->number_of_philos)
			if ((philos)[i])
				free((philos)[i]);
		free(philos);
	}
	pthread_mutex_destroy(&info->eat_count_mutex);
}

static t_philo	*init_philo(int num, t_info *info, t_pf *pf)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof (t_philo));
	if (!philo)
		return (NULL);
	philo->num = num;
	philo->info = info;
	philo->pf = pf;
	philo->eat_count = 0;
	philo->last_eat = &info->start_time;
	if (gettimeofday(philo->last_eat, NULL))
		return (free(philo), NULL);
	return (philo);
}

static t_philo	**init_philos(t_info *info, t_pf *pf)
{
	int		i;
	t_philo	**args;

	pf->philos = malloc(info->number_of_philos * sizeof (pthread_t));
	pf->forks = malloc(info->number_of_philos * sizeof (pthread_mutex_t));
	args = malloc(info->number_of_philos * sizeof (t_philo *));
	if (!pf->philos || !pf->forks || !args)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philos)
		if (pthread_mutex_init(&pf->forks[i], NULL))
			return (NULL);
	i = -1;
	while (++i < info->number_of_philos)
	{
		args[i] = init_philo(i + 1, info, pf);
		if (!args[i] || pthread_create(&pf->philos[i], NULL,
				&philo_routine, args[i]))
			return (NULL);
	}
	i = -1;
	while (++i < info->number_of_philos)
		if (pthread_detach(pf->philos[i]))
			return (NULL);
	return (args);
}

static void	*finish_control(void *args)
{
	int				i;
	t_philo			**philos;
	t_info			*info;

	philos = (t_philo **)args;
	if (!philos || !philos[0])
		return (NULL);
	info = philos[0]->info;
	while (!info->finished)
	{
		if (info->must_eat != -1 && info->total_ate >= info->number_of_philos)
			return (info->finished = 1, NULL);
		i = -1;
		while (++i < info->number_of_philos)
		{
			if (get_ms(philos[i]->last_eat) < (get_current_ms() - \
					info->time_to_die))
				return (info->finished = 1, print_died(get_ms_from_start(
							philos[i]->info->start_time), philos[i]), NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_pf		pf;
	t_philo		**philos;
	pthread_t	finish_check_thread;

	if (!parse_args(argc, argv, &info))
		return (0);
	philos = init_philos(&info, &pf);
	if (!philos)
		return (clean_up(&info, &pf, NULL), 0);
	if (!pthread_create(&finish_check_thread, NULL, &finish_control, philos))
		pthread_join(finish_check_thread, NULL);
	usleep(2000);
	clean_up(&info, &pf, philos);
	return (0);
}
