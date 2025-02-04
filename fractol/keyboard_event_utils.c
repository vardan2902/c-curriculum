/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:12:32 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 18:03:02 by vapetros         ###   ########.fr       */
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

void	change_fractal(int key, t_env *env, int should_convert_key)
{
	if (should_convert_key)
	{
		if (key == KEY_5)
			key = 4;
		if (key == KEY_6)
			key = 5;
		if (key == KEY_7)
			key = 6;
		if (key == KEY_8)
			key = 7;
		if (key == KEY_9)
			key = 8;
	}
	env->formula_name = key;
	reset_params(env);
}
