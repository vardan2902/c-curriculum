/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:59:26 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/13 20:57:16 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_ms(int ms, t_general_info *info)
{
	t_timeval	current_tv;
	long int	start_ms;
	long int	current_ms;
	
	if (gettimeofday(&current_tv, NULL) == -1)
		return ;
	start_ms = current_tv.tv_sec * 1000 + current_tv.tv_usec / 1000;
	while (1)
	{
		if (info->philo_died || gettimeofday(&current_tv, NULL) == -1)
			return ;
		current_ms = current_tv.tv_sec * 1000 + current_tv.tv_usec / 1000;
		if (start_ms + ms <= current_ms)
			return ;
		usleep(100);
	}
}

int	get_ms(t_timeval *tv)
{
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}

int	get_ms_from_start(t_timeval tv)
{
	t_timeval	current_tv;

	if (gettimeofday(&current_tv, NULL) == -1)
		return -1;
	return (get_ms(&current_tv) - get_ms(&tv));
}

int	get_current_ms()
{	
	t_timeval	current_tv;
	
	if (gettimeofday(&current_tv, NULL) == -1)
		return -1;
	return (get_ms(&current_tv));
}
