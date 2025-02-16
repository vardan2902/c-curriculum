/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:35:30 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/14 22:05:05 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_atoi(const char *str)
{
	int			i;
	long int	num;

	if (str[0] == '\0')
		return (-1);
	if (str[0] == '0' && str[1])
		return (-1);
	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
	i = 0;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX || num < INT_MIN)
			return (-1);
		++i;
	}
	return (num);
}

int	parse_args(int argc, char *argv[], t_info *info)
{
	if (argc < 5 || argc > 6)
		return (print_usage(argv[0]), 0);
	info->must_eat = -1;
	info->number_of_philos = philo_atoi(argv[1]);
	info->time_to_die = philo_atoi(argv[2]);
	info->time_to_eat = philo_atoi(argv[3]);
	info->time_to_sleep = philo_atoi(argv[4]);
	if (info->number_of_philos <= 0 || info->time_to_die <= 0
		|| info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (print_usage(argv[0]), 0);
	if (argc == 6)
	{
		info->must_eat = philo_atoi(argv[5]);
		if (info->must_eat <= 0)
			return (print_usage(argv[0]), 0);
	}
	sem_unlink(EAT_COUNT_SEM);
	sem_unlink(DIED_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(FINISH_SEM);
	sem_unlink(FORK_GUARD_SEM);
	info->eat_count_sem = sem_open(EAT_COUNT_SEM, O_CREAT, 0644, 0);
	info->died_sem = sem_open(DIED_SEM, O_CREAT, 0644, 0);
	info->print_sem = sem_open(PRINT_SEM, O_CREAT, 0644, 1);
	info->finish_sem = sem_open(FINISH_SEM, O_CREAT, 0644, 0);
	info->fork_guard_sem = sem_open(FORK_GUARD_SEM, O_CREAT, 0644, 1);
	if (info->eat_count_sem == SEM_FAILED || info->died_sem == SEM_FAILED)
		return (0);
	return (1);
}
