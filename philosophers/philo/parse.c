/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:35:30 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/17 15:37:33 by vapetros         ###   ########.fr       */
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

void	init_arg_info(int argc, char *argv[], t_info *info)
{
	info->number_of_philos = philo_atoi(argv[1]);
	info->time_to_die = philo_atoi(argv[2]);
	info->time_to_eat = philo_atoi(argv[3]);
	info->time_to_sleep = philo_atoi(argv[4]);
	info->must_eat = -1;
	if (argc == 6)
		info->must_eat = philo_atoi(argv[5]);
}

int	parse_args(int argc, char *argv[], t_info *info)
{
	if (argc < 5 || argc > 6)
		return (print_usage(argv[0]), 0);
	init_arg_info(argc, argv, info);
	if (info->number_of_philos <= 0 || info->number_of_philos > 200
		|| info->time_to_die < 60 || info->time_to_eat < 60
		|| info->time_to_sleep < 60 || (argc == 6 && info->must_eat == -1))
		return (print_usage(argv[0]), 0);
	info->finished = 0;
	if (pthread_mutex_init(&info->eat_count_mutex, NULL)
		|| pthread_mutex_init(&info->print_mutex, NULL))
		return (0);
	if (gettimeofday(&info->start_time, NULL) == -1)
		return (0);
	return (1);
}
