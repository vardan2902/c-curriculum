/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:59:26 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/16 21:36:50 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_ms(t_timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

void	wait_ms(int ms)
{
	t_timeval	current_tv;
	long int	start_ms;
	long int	current_ms;

	if (gettimeofday(&current_tv, NULL) == -1)
		return ;
	start_ms = get_ms(&current_tv);
	while (1)
	{
		if (gettimeofday(&current_tv, NULL) == -1)
			return ;
		current_ms = get_ms(&current_tv);
		if (start_ms + ms <= current_ms)
			return ;
		usleep(100);
	}
}

int	get_ms_from_start(t_timeval tv)
{
	t_timeval	current_tv;

	if (gettimeofday(&current_tv, NULL) == -1)
		return (-1);
	return (get_ms(&current_tv) - get_ms(&tv) - 2000);
}

void	wait_untill_sim_start(t_timeval *tv)
{
	t_timeval	current_tv;
	long int	start_ms;
	long int	current_ms;

	if (gettimeofday(&current_tv, NULL) == -1)
		return ;
	start_ms = get_ms(tv) + 2000;
	while (1)
	{
		if (gettimeofday(&current_tv, NULL) == -1)
			return ;
		current_ms = get_ms(&current_tv);
		if (start_ms <= current_ms)
			return ;
		usleep(100);
	}
}

int	get_current_ms(void)
{
	t_timeval	current_tv;

	if (gettimeofday(&current_tv, NULL) == -1)
		return (-1);
	return (get_ms(&current_tv));
}
