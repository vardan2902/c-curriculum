/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:08 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 20:57:11 by vapetros         ###   ########.fr       */
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
