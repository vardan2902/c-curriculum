/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:48:57 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 22:41:14 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	burning_ship(t_complex z, t_env *env)
{
	z = c_abs(z);
	z = c_sqrt(z);
	return (add(z, map_point(env)));
}

t_complex	celtic_mandelbrot(t_complex z, t_env *env)
{
	t_complex	result;

	result = c_sqrt(z);
	result = c_sqrt(result);
	result.x = fabs(result.x);
	return (add(result, map_point(env)));
}

t_complex	perpendicular_buffalo(t_complex z, t_env *env)
{
	z = c_abs(c_sqrt(z));
	z.y = -z.y;
	return (add(z, map_point(env)));
}

t_complex	cubic_mandelbrot(t_complex z, t_env *env)
{
	z = c_power(z, 3);
	return (add(z, map_point(env)));
}
