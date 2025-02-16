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

void	print_usage(char *name)
{
	printf("%s:\tusage:\tnumber_of_philosophers time_to_die" \
" time_to_eat time_to_sleep\n\t\t\t[number_of_times_each_philosopher" \
"_must_eat]\n", name);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_state(const char *state, t_philo *philo)
{
	sem_wait(philo->info->print_sem);
	printf("%d %d %s\n", get_ms_from_start(philo->info->start_time),
		philo->num, state);
	if (ft_strcmp(state, "died"))
		sem_post(philo->info->print_sem);
}
