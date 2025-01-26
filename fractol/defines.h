/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:33:35 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/26 23:33:37 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_SIZE 800
# define ZOOM 1.1
# define ITERATIONS 256

typedef enum e_formula
{
	BUFFALO,
	MANDELBROT,
	TRICORN,
	JULIA
}	t_formula;

enum	e_keycodes
{
	KEY_ESC		=	53,
	KEY_L		=	37,
	KEY_ZERO	=	29,
	KEY_ONE		=	18,
	KEY_FOUR	=	21,
	KEY_Q		=	12,
	KEY_W		=	13,
	KEY_E		=	14,
	KEY_A		=	0,
	KEY_S		=	1,
	KEY_D		=	2,
	KEY_UP		=	126,
	KEY_DOWN	=	125,
	KEY_LEFT	=	123,
	KEY_RIGHT	=	124,
};

enum	e_mousecodes
{
	SCROLL_DOWN	=	4,
	SCROLL_UP	=	5,
};

#endif
