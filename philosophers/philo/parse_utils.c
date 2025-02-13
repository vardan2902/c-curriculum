/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:45:42 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/11 18:21:22 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_atoi(const char *str)
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
