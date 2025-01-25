/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:48:31 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/20 19:37:22 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_percentage(t_flags flags, const char **format, int *size)
{
	int	padding;

	padding = flags.width - 1;
	if (flags.precision > 1)
		padding -= (flags.precision - 1);
	if (!flags.left_align)
		print_padding(padding, ' ', size);
	ft_putchar_fd(**format, 1);
	if (flags.left_align)
		print_padding(padding, ' ', size);
	++(*size);
	++(*format);
}

void	print_conversion(va_list ap, const char **format, int *size)
{
	t_flags	flags;

	flags = extract_flags(format);
	if (**format == 'd' || **format == 'i')
		print_decimal(ap, flags, format, size);
	else if (**format == 'u')
		print_unsigned_decimal(ap, flags, format, size);
	else if (**format == 'c')
		print_char(ap, flags, format, size);
	else if (**format == 's')
		print_string(ap, flags, format, size);
	else if (**format == 'x' || **format == 'X')
		print_hex(ap, flags, format, size);
	else if (**format == 'p')
		print_pointer(ap, flags, format, size);
	else if (**format == '%')
		print_percentage(flags, format, size);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		print_size;

	print_size = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			print_conversion(ap, &format, &print_size);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			++print_size;
			++format;
		}
	}
	va_end(ap);
	return (print_size);
}
