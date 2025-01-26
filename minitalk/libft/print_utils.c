/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:22:10 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/25 18:10:58 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_padding(int len, char pad_char, int *size)
{
	while (len-- > 0)
	{
		ft_putchar_fd(pad_char, 1);
		++(*size);
	}
}

void	print_hex_alternate(const char **format, int *size)
{
	if (**format == 'X')
		write(1, "0X", 2);
	else
		write(1, "0x", 2);
	*size += 2;
}

void	print_sign(int is_negative, t_flags flags, int *size)
{
	if (is_negative)
		write(1, "-", 1);
	else
	{
		if (flags.plus)
			*size += write(1, "+", 1);
		else if (flags.space)
			*size += write(1, " ", 1);
	}
}
