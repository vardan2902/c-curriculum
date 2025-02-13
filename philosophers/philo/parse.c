/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:35:30 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/13 21:06:13 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char *argv[], t_general_info *info)
{
	if (argc < 5 || argc > 6)
		return (print_usage(argv[0]), 0);
	info->must_eat = -1;
	info->number_of_philos = philo_atoi(argv[1]);
	info->time_to_die = philo_atoi(argv[2]);
	info->time_to_eat = philo_atoi(argv[3]);
	info->time_to_sleep = philo_atoi(argv[4]);
	if (info->number_of_philos <= 0 || info->time_to_die == -1
		|| info->time_to_eat == -1 || info->time_to_sleep == -1)
		return (print_usage(argv[0]), 0);
	if (argc == 6)
	{
		info->must_eat = philo_atoi(argv[5]);
		if (info->must_eat == -1)
			return (print_usage(argv[0]), 0);
	}
	info->philo_died = 0;
	info->finished = 0;
	if (gettimeofday(&info->start_time, NULL) == -1)
		return (0);
	return (1);
}
