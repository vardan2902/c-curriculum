/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:08:52 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/25 17:47:42 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_hex_helper(unsigned long num, int *size, char *base)
{
	char	buffer[16];
	int		i;

	i = 0;
	if (num == 0)
		buffer[i++] = '0';
	else
	{
		while (num > 0)
		{
			buffer[i++] = base[num % 16];
			num /= 16;
		}
	}
	while (i > 0)
	{
		write(1, &buffer[--i], 1);
		++(*size);
	}
}

static size_t	get_hex_len(unsigned long num)
{
	size_t			len;
	unsigned long	temp;

	temp = num;
	len = 0;
	while (temp > 0)
	{
		temp /= 16;
		++len;
	}
	if (num == 0)
		len = 1;
	return (len);
}

void	print_hex(va_list ap, t_flags flags, const char **format, int *size)
{
	unsigned int	num;
	int				len;
	int				padding;
	char			*base;

	num = va_arg(ap, unsigned int);
	len = get_hex_len(num);
	base = "0123456789abcdef";
	if (**format == 'X')
		base = "0123456789ABCDEF";
	padding = get_padding_util(flags, len);
	if (should_print_alternate(0, flags, num))
		print_hex_alternate(format, size);
	if (!flags.left_align)
		print_padding(get_hex_pad_len(padding, flags, num),
			get_pad_char(flags), size);
	if (should_print_alternate(1, flags, num))
		print_hex_alternate(format, size);
	if (flags.precision_specified)
		print_padding(flags.precision - len, '0', size);
	if (!(num == 0 && flags.precision == 0))
		print_hex_helper(num, size, base);
	if (flags.left_align)
		print_padding(get_hex_pad_len(padding, flags, num), ' ', size);
	++(*format);
}

static void	print_pointer_with_flags(unsigned long ptr, t_flags flags,
	int *size)
{
	int	len;
	int	padding;

	len = get_hex_len(ptr);
	if (flags.precision_specified && flags.precision > len)
		len = flags.precision;
	if (flags.width > len + 2)
		padding = flags.width - (len + 2);
	else
		padding = 0;
	if (!flags.left_align)
		print_padding(padding, ' ', size);
	if (flags.precision_specified)
		print_padding(flags.precision - ((ptr != 0) && \
			(len - (len - flags.precision))), '0', size);
	*size += write(1, "0x", 2);
	print_hex_helper(ptr, size, "0123456789abcdef");
	if (flags.left_align)
		print_padding(padding, ' ', size);
}

void	print_pointer(va_list ap, t_flags flags, const char **format, int *size)
{
	unsigned long	ptr;

	ptr = (unsigned long)va_arg(ap, void *);
	print_pointer_with_flags(ptr, flags, size);
	++(*format);
}
