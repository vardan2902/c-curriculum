/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:28:18 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 23:28:43 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_env
{
	int					scrolling;
	t_formula			formula_name;
	t_complex			c;
	t_data				data;
	t_mlx				mlx;
	int					lock;
	double				r;
	t_color				color;
	int					x;
	int					y;
	double				off_x;
	double				off_y;
	t_complex			(*formula[4])(t_complex, struct s_env *);
}	t_env;

#endif
