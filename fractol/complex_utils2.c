/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:06:59 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 19:16:53 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_mult(t_complex a, t_complex b)
{
	t_complex	c;

	c.x = a.x * b.x - a.y * b.y;
	c.y = a.x * b.y + a.y * b.x;
	return (c);
}

t_complex	c_div(t_complex a, t_complex b)
{
	t_complex	c;
	double		denom;

	denom = b.x * b.x + b.y * b.y;
	c.x = (a.x * b.x + a.y * b.y) / denom;
	c.y = (a.y * b.x - a.x * b.y) / denom;
	return (c);
}

t_complex	c_sub(t_complex a, t_complex b)
{
	t_complex	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

t_complex	c_power(t_complex a, int exp)
{
	t_complex	result;
	int			i;

	result = a;
	i = 1;
	while (i < exp)
	{
		result = c_mult(result, a);
		i++;
	}
	return (result);
}

t_complex	init_complex(double x, double y)
{
	t_complex	z;

	z.x = x;
	z.y = y;
	return (z);
}
