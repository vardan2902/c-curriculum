/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:51:58 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 23:21:14 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

double		c_mod(t_complex a);
t_complex	c_abs(t_complex c);
t_complex	add(t_complex a, t_complex b);
t_complex	c_sqrt(t_complex a);
t_complex	rev_imaginary(t_complex c);
t_complex	init_complex(double x, double y);
t_complex	map_point(t_env *env);
int			draw_fractal(t_env *env);
void		check_args(int argc, char **argv);
int			get_formula_name(char **argv);
double		ft_atof(const char *str);
int			on_key_press(int keycode, t_env *env);
void		move(t_env *env, int key);
void		add_color(int key, t_env *env);
void		sub_color(int key, t_env *env);
void		change_fractal(int key, t_env *env);
void		reset_params(t_env *env);
int			on_mouse_move(int x, int y, t_env *env);
int			on_scroll(int button, int x, int y, t_env *env);
int			mlx_close(t_mlx *mlx);

#endif
