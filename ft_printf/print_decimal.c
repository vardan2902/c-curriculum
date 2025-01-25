/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:26:13 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/25 19:29:22 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_precision(t_flags flags, int len, int *size)
{
	if (flags.precision_specified && flags.precision > len)
		print_padding(flags.precision - len, '0', size);
}

static void	handle_padding(t_pad pad, int is_negative, t_flags flags,
	int *size)
{
	if (pad.pad_char == '0')
		print_sign(is_negative, flags, size);
	if (!flags.left_align)
		print_padding(pad.padding, pad.pad_char, size);
	if (pad.pad_char != '0')
		print_sign(is_negative, flags, size);
}

void	print_decimal(va_list ap, t_flags flags, const char **format, int *size)
{
	int		num;
	char	*str;
	int		len;
	t_pad	pad;

	pad.pad_char = get_pad_char(flags);
	num = va_arg(ap, int);
	str = ft_itoa(num);
	len = ft_strlen(str);
	pad.padding = get_pad_len(flags, num, len, str[0] == '-');
	handle_padding(pad, str[0] == '-', flags, size);
	handle_precision(flags, len - (str[0] == '-'), size);
	if (!(num == 0 && flags.precision == 0))
	{
		write(1, str + (str[0] == '-'), ft_strlen(str) - (str[0] == '-'));
		(*size) += ft_strlen(str);
	}
	if (flags.left_align)
		print_padding(pad.padding, ' ', size);
	free(str);
	++(*format);
}
