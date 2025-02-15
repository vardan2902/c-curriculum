/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:17:57 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/14 21:45:59 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork_taken(t_philo *philo)
{
	printf(YELLOW"%d %d has taken a fork"RESET"\n",
		get_ms_from_start(philo->info->start_time), philo->num);
}

void	print_eating(t_philo *philo)
{
	printf(CYAN"%d %d is eating"RESET"\n",
		get_ms_from_start(philo->info->start_time), philo->num);
}

void	print_sleeping(t_philo *philo)
{
	printf(GREEN"%d %d is sleeping"RESET"\n",
		get_ms_from_start(philo->info->start_time), philo->num);
}

void	print_thinking(t_philo *philo)
{
	printf(HGREEN"%d %d is thinking"RESET"\n",
		get_ms_from_start(philo->info->start_time), philo->num);
}

void	print_died(t_philo *philo)
{
	printf(RED"%d %d died"RESET"\n",
		get_ms_from_start(philo->info->start_time), philo->num);
}
