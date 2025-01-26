/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:34:16 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 23:34:53 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_scroll(int button, int x, int y, t_env *env)
{
	double	mouse_x;
	double	mouse_y;
	double	zoom_factor;

	if (env->scrolling)
		return (0);
	env->scrolling = 1;
	mouse_x = (x - WIN_SIZE / 2) / (double)WIN_SIZE * env->r + env->off_x;
	mouse_y = (y - WIN_SIZE / 2) / (double)WIN_SIZE * env->r + env->off_y;
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
	env->off_x += (mouse_x - env->off_x) * (1.0 - zoom_factor);
	env->off_y += (mouse_y - env->off_y) * (1.0 - zoom_factor);
	env->scrolling = 0;
	return (0);
}

int	mlx_close(t_mlx *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	ft_printf("Bye!\n");
	exit(0);
	return (0);
}

int	on_mouse_move(int x, int y, t_env *env)
{
	if (env->lock < 0 || env->formula_name != JULIA)
		return (0);
	env->c.x = ((x - WIN_SIZE / 2) * env->r / WIN_SIZE) * 2 + env->off_x;
	env->c.y = ((y - WIN_SIZE / 2) * env->r / WIN_SIZE) * 2 + env->off_y;
	return (0);
}

int	on_key_press(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		mlx_close(&env->mlx);
	else if (keycode == KEY_L)
		env->lock *= -1;
	else if (keycode == KEY_ZERO)
		reset_params(env);
	else if (keycode >= KEY_ONE && keycode <= KEY_FOUR)
		change_fractal(keycode - 18, env);
	else if (keycode == KEY_Q || keycode == KEY_W || keycode == KEY_E)
		add_color(keycode, env);
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		sub_color(keycode, env);
	else if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		move(env, keycode);
	return (0);
}
