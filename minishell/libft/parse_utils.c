/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:01:46 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/25 18:03:51 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_number(const char **format)
{
	int	number;

	number = 0;
	while (ft_isdigit(**format))
	{
		number = number * 10 + (**format - '0');
		++(*format);
	}
	return (number);
}

static void	set_flag(t_flags *flags, char flag_char)
{
	if (flag_char == '-')
	{
		flags->left_align = 1;
		flags->zero_pad = 0;
	}
	else if (flag_char == '0' && !flags->left_align)
		flags->zero_pad = 1;
	else if (flag_char == '#')
		flags->alternate = 1;
	else if (flag_char == ' ')
		flags->space = !flags->plus;
	else if (flag_char == '+')
	{
		flags->plus = 1;
		flags->space = 0;
	}
}

static void	set_precision(t_flags *flags, const char **format)
{
	(*format)++;
	flags->precision_specified = 1;
	flags->precision = 0;
	if (ft_isdigit(**format))
		flags->precision = parse_number(format);
}

t_flags	extract_flags(const char **format)
{
	t_flags	flags;

	flags.left_align = 0;
	flags.zero_pad = 0;
	flags.width = 0;
	flags.precision = -1;
	flags.precision_specified = 0;
	flags.alternate = 0;
	flags.space = 0;
	flags.plus = 0;
	while (**format)
	{
		if (ft_strchr("-0# +", **format))
			set_flag(&flags, *(*format)++);
		else if (ft_isdigit(**format))
			flags.width = parse_number(format);
		else if (**format == '.')
			set_precision(&flags, format);
		else
			break ;
	}
	return (flags);
}
