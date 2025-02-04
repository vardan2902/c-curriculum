/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:04:25 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 22:31:30 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_params(t_env *env)
{
	env->color.r = 5;
	env->color.g = 0;
	env->color.b = 0;
	env->r = 2;
	env->off_x = 0;
	env->off_y = 0;
}

void	init_formulas(t_env *env)
{
	env->formula[JULIA] = julia;
	env->formula[MANDELBROT] = mandelbrot;
	env->formula[BUFFALO] = buffalo;
	env->formula[TRICORN] = tricorn;
	env->formula[NEWTON] = newton;
	env->formula[BURNING_SHIP] = burning_ship;
	env->formula[CELTIC_MANDELBROT] = celtic_mandelbrot;
	env->formula[PERPENDICULAR_BUFFALO] = perpendicular_buffalo;
	env->formula[CUBIC_MANDELBROT] = cubic_mandelbrot;
}

t_env	init_env(int argc, char **argv)
{
	t_env	env;
	double	x;
	double	y;

	x = 0.284;
	y = -0.120;
	env.mlx.mlx = mlx_init();
	env.update_needed = 1;
	env.mlx.win = mlx_new_window(env.mlx.mlx, WIN_SIZE, WIN_SIZE, "fractol");
	env.data.img = mlx_new_image(env.mlx.mlx, WIN_SIZE, WIN_SIZE);
	env.data.addr = mlx_get_data_addr(env.data.img, &env.data.bits_per_pixel,
			&env.data.line_length, &env.data.endian);
	env.lock = -1;
	env.formula_name = get_formula_name(argv);
	if (argc > 2)
		x = ft_atof(argv[2]);
	if (argc > 3)
		y = ft_atof(argv[3]);
	env.c = init_complex(x, y);
	init_formulas(&env);
	reset_params(&env);
	return (env);
}

int	main(int argc, char **argv)
{
	t_env	env;

	check_args(argc, argv);
	env = init_env(argc, argv);
	mlx_hook(env.mlx.win, 2, 1L << 0, on_key_press, &env);
	mlx_hook(env.mlx.win, 6, 1L << 6, on_mouse_move, &env);
	mlx_hook(env.mlx.win, 4, 1L << 8, on_scroll, &env);
	mlx_hook(env.mlx.win, 17, 1L << 0, mlx_close, &env.mlx);
	mlx_loop_hook(env.mlx.mlx, draw_fractal, &env);
	mlx_loop(env.mlx.mlx);
	return (0);
}
