/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:59:26 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/18 15:39:45 by vapetros         ###   ########.fr       */
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

	if (gettimeofday(&current_tv, NULL) == -1)
		return ;
	start_ms = get_ms(&current_tv);
	while (gettimeofday(&current_tv, NULL) != -1 && !usleep(100))
		if (start_ms + ms <= get_ms(&current_tv))
			return ;
}

int	get_ms_from_start(t_timeval tv, int offset)
{
	t_timeval	current_tv;

	if (gettimeofday(&current_tv, NULL) == -1)
		return (-1);
	return (get_ms(&current_tv) - get_ms(&tv) - offset);
}

void	wait_untill_sim_start(t_timeval *tv, int offset)
{
	t_timeval	current_tv;
	long int	start_ms;

	if (gettimeofday(&current_tv, NULL) == -1)
		return ;
	start_ms = get_ms(tv) + offset;
	while (gettimeofday(&current_tv, NULL) != -1 && !usleep(100))
		if (start_ms <= get_ms(&current_tv))
			return ;
}

int	get_current_ms(void)
{
	t_timeval	current_tv;

	if (gettimeofday(&current_tv, NULL) == -1)
		return (-1);
	return (get_ms(&current_tv));
}
