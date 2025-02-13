/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:17:57 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/13 21:03:27 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork_taken(int ms, t_philo *philo)
{
	if (!philo->info->philo_died)
		printf(YELLOW"%d %d has taken a fork\n"RESET, ms, philo->num);
}

void	print_eating(int ms, t_philo *philo)
{
	if (!philo->info->philo_died)
		printf(CYAN"%d %d is eating\n"RESET, ms, philo->num);
}

void	print_sleeping(int ms, t_philo *philo)
{
	if (!philo->info->philo_died)
		printf(GREEN"%d %d is sleeping\n"RESET, ms, philo->num);
}

void	print_thinking(int ms, t_philo *philo)
{
	if (!philo->info->philo_died)
		printf(HGREEN"%d %d is thinking\n"RESET, ms, philo->num);
}

void	print_died(int ms, t_philo *philo)
{
	printf(RED"%d %d died\n"RESET, ms, philo->num);
}
