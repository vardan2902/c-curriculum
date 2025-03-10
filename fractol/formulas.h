/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:02:25 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 19:06:28 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMULAS_H
# define FORMULAS_H

t_complex	julia(t_complex z, t_env *env);
t_complex	mandelbrot(t_complex z, t_env *env);
t_complex	buffalo(t_complex z, t_env *env);
t_complex	tricorn(t_complex z, t_env *env);
t_complex	newton(t_complex z, t_env *env);
t_complex	burning_ship(t_complex z, t_env *env);
t_complex	celtic_mandelbrot(t_complex z, t_env *env);
t_complex	perpendicular_buffalo(t_complex z, t_env *env);
t_complex	cubic_mandelbrot(t_complex z, t_env *env);

#endif
