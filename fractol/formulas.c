/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:08 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 22:42:13 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	julia(t_complex z, t_env *env)
{
	return (add(c_sqrt(z), env->c));
}

t_complex	mandelbrot(t_complex z, t_env *env)
{
	return (add(c_sqrt(z), map_point(env)));
}

t_complex	buffalo(t_complex z, t_env *env)
{
	return (add(c_abs(c_sqrt(z)), map_point(env)));
}

t_complex	tricorn(t_complex z, t_env *env)
{
	return (add(rev_imaginary(c_sqrt(z)), map_point(env)));
}

t_complex	newton(t_complex z, t_env *env)
{
	t_complex	num;
	t_complex	den;
	t_complex	c;
	double		epsilon;

	epsilon = 1e-6;
	c = env->c;
	num = c_sub(c_power(z, 3), c);
	den = c_mult(c_power(z, 2), init_complex(3, 0));
	if (c_mod(den) < epsilon)
		return (z);
	return (c_sub(z, c_div(num, den)));
}
