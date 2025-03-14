/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:17:35 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/04 22:40:43 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	to_lower(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		s[i] = ft_tolower(s[i]);
}

static void	print_usage_exit(char *name)
{
	ft_printf(ANSI_BRIGHT_RED"%s:\tInvalid Arguments\n"ANSI_RESET, name);
	ft_printf(ANSI_BRIGHT_CYAN"Usage:\t\tjulia [x] [y]\n\t\tmandelbrot\n"\
			ANSI_RESET);
	exit(1);
}

static int	is_valid_float(const char *str)
{
	int	seen_digit;
	int	seen_dot;

	seen_digit = 0;
	seen_dot = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			seen_digit = 1;
		else if (*str == '.' && !seen_dot)
			seen_dot = 1;
		else
			return (0);
		str++;
	}
	return (seen_digit);
}

void	check_args(int argc, char **argv)
{
	if (argc == 1 || argc > 4)
		print_usage_exit(argv[0]);
	to_lower(argv[1]);
	if (ft_strcmp(argv[1], "julia") && ft_strcmp(argv[1], "mandelbrot"))
		print_usage_exit(argv[0]);
	if (argc > 2)
	{
		if (ft_strcmp(argv[1], "julia"))
			print_usage_exit(argv[0]);
		if (!is_valid_float(argv[2]) || (argc > 3 && !is_valid_float(argv[3])))
			print_usage_exit(argv[0]);
	}
}

int	get_formula_name(char **argv)
{
	if (!ft_strcmp(argv[1], "julia"))
		return (JULIA);
	if (!ft_strcmp(argv[1], "mandelbrot"))
		return (MANDELBROT);
	print_usage_exit(argv[0]);
	return (0);
}
