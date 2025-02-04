/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:25:05 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/05 00:01:01 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	map_point(t_env *env)
{
	t_complex	c;

	c.x = ((env->x - WIN_SIZE / 2) * env->r / WIN_SIZE) * 2 + env->off_x;
	c.y = ((env->y - WIN_SIZE / 2) * env->r / WIN_SIZE) * 2 + env->off_y;
	return (c);
}

int	calculate_fractal(t_env *env)
{
	t_complex	prev_z;
	t_complex	z;
	int			i;
	double		epsilon;

	epsilon = 1e-6;
	z = init_complex(0, 0);
	if (env->formula_name == JULIA || env->formula_name == NEWTON)
		z = map_point(env);
	i = -1;
	while (c_mod(z) <= 2 && ++i < ITERATIONS)
	{
		prev_z = z;
		z = env->formula[env->formula_name](z, env);
		if (env->formula_name == NEWTON && c_mod(c_sub(z, prev_z)) < epsilon)
			return (i);
		if (env->formula_name != NEWTON && c_mod(z) >= 2)
			return (i);
	}
	return (0);
}

void	set_pixel(t_env *env, double res)
{
	char	*dst;

	dst = env->data.addr + (env->y * env->data.line_length + env->x * \
			(env->data.bits_per_pixel / 8));
	*(unsigned char *)(dst + 0) = (unsigned char)(env->color.b * res) % 256;
	*(unsigned char *)(dst + 1) = (unsigned char)(env->color.g * res) % 256;
	*(unsigned char *)(dst + 2) = (unsigned char)(env->color.r * res) % 256;
	*(unsigned char *)(dst + 3) = 0;
}

int	draw_fractal(t_env *env)
{
	int	res;

	if (!env->update_needed)
		return (0);
	env->x = -1;
	while (++(env->x) < WIN_SIZE)
	{
		env->y = -1;
		while (++(env->y) < WIN_SIZE)
		{
			res = calculate_fractal(env);
			set_pixel(env, res);
		}
	}
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->data.img, 0, 0);
	env->update_needed = 0;
	return (0);
}
