/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:39:22 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/11 18:16:11 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(char *name)
{
	printf(RED"%s:\tusage:\tnumber_of_philosophers time_to_die" \
" time_to_eat time_to_sleep\n\t\t\t[number_of_times_each_philosopher" \
"_must_eat]\n"RESET, name);
}
