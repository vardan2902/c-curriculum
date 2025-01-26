/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:51:07 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 23:32:49 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_abs(t_complex c)
{
	if (c.x < 0)
		c.x *= -1;
	if (c.y < 0)
		c.y *= -1;
	return (c);
}

t_complex	add(t_complex a, t_complex b)
{
	t_complex	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_complex	c_sqrt(t_complex a)
{
	t_complex	c;

	c.x = a.x * a.x - a.y * a.y;
	c.y = 2 * a.x * a.y;
	return (c);
}

double	c_mod(t_complex a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_complex	rev_imaginary(t_complex c)
{
	c.y *= -1;
	return (c);
}
