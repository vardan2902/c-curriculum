/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:35:57 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 23:38:50 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0.0;
	fraction = 0.1;
	sign = get_sign(&str);
	while (*str && ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str && ft_isdigit(*str))
		{
			result += fraction * (*str - '0');
			fraction *= 0.1;
			str++;
		}
	}
	result *= sign;
	return (result);
}
