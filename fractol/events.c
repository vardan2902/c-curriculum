/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:34:16 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 23:54:05 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_scroll(int button, int x, int y, t_env *env)
{
	double	center;
	double	zoom_factor;

	if (env->update_needed)
		return (0);
	if (button == SCROLL_UP)
	{
		zoom_factor = 1.0 / ZOOM;
		env->r /= ZOOM;
	}
	else if (button == SCROLL_DOWN)
	{
		zoom_factor = ZOOM;
		env->r *= ZOOM;
	}
	else
		return (0);
	center = WIN_SIZE / 2.0;
	env->off_x -= (x - center) / WIN_SIZE * 2 * \
					(env->r - env->r / zoom_factor);
	env->off_y -= (y - center) / WIN_SIZE * 2 * \
					(env->r - env->r / zoom_factor);
	env->update_needed = 1;
	return (0);
}

int	mlx_close(t_mlx *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	ft_printf(ANSI_BRIGHT_YELLOW"Bye!\n"ANSI_RESET);
	exit(0);
	return (0);
}

int	on_mouse_move(int x, int y, t_env *env)
{
	double	center;
	double	scale_factor;

	if (env->update_needed)
		return (0);
	if (env->lock < 0
		|| !(env->formula_name == JULIA || env->formula_name == NEWTON))
		return (0);
	center = (double)WIN_SIZE / 2.0;
	scale_factor = env->r / (double)WIN_SIZE * 2.0;
	env->c.x = ((x - center) * scale_factor) + env->off_x;
	env->c.y = ((y - center) * scale_factor) + env->off_y;
	env->update_needed = 1;
	return (0);
}

int	on_key_press(int keycode, t_env *env)
{
	if (env->update_needed)
		return (0);
	env->update_needed = 1;
	if (keycode == KEY_ESC)
		mlx_close(&env->mlx);
	else if (keycode == KEY_L)
		env->lock *= -1;
	else if (keycode == KEY_0)
		reset_params(env);
	else if (keycode >= KEY_1 && keycode <= KEY_4)
		change_fractal(keycode - 18, env, 0);
	else if (keycode == KEY_5 || keycode == KEY_6 || keycode == KEY_7
		|| keycode == KEY_8 || keycode == KEY_9)
		change_fractal(keycode, env, 1);
	else if (keycode == KEY_Q || keycode == KEY_W || keycode == KEY_E)
		add_color(keycode, env);
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		sub_color(keycode, env);
	else if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		move(env, keycode);
	else
		env->update_needed = 0;
	return (0);
}
