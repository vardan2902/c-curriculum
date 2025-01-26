/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:12:32 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 23:41:55 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move(t_env *env, int key)
{
	if (key == KEY_UP)
		env->off_y -= env->r / 10;
	else if (key == KEY_DOWN)
		env->off_y += env->r / 10;
	else if (key == KEY_RIGHT)
		env->off_x += env->r / 10;
	else if (key == KEY_LEFT)
		env->off_x -= env->r / 10;
}

void	add_color(int key, t_env *env)
{
	if (key == KEY_Q)
		env->color.r = (unsigned char)(env->color.r + 5);
	else if (key == KEY_W)
		env->color.g = (unsigned char)(env->color.g + 5);
	else if (key == KEY_E)
		env->color.b = (unsigned char)(env->color.b + 5);
}

void	sub_color(int key, t_env *env)
{
	if (key == KEY_A)
		env->color.r = (unsigned char)(env->color.r - 5);
	else if (key == KEY_S)
		env->color.g = (unsigned char)(env->color.g - 5);
	else if (key == KEY_D)
		env->color.b = (unsigned char)(env->color.b - 5);
}

void	change_fractal(int key, t_env *env)
{
	env->formula_name = key;
	reset_params(env);
}
