/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_udecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:11:05 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/25 19:47:44 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

static char	*ft_utoa(unsigned int n)
{
	int					len;
	char				*result;
	unsigned int		m;

	m = n;
	len = 0;
	if (m == 0)
		len = 1;
	while (m)
	{
		m /= 10;
		++len;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[--len] = ft_abs((n % 10)) + 48;
		n /= 10;
	}
	return (result);
}

int	get_full_pad(int padding, int num, t_flags flags)
{
	if (flags.width && num == 0 && flags.precision == 0)
		return (padding + 1);
	return (padding);
}

void	print_unsigned_decimal(va_list ap, t_flags flags, const char **format,
	int *size)
{
	unsigned int	num;
	char			*str;
	int				len;
	int				padding;
	char			pad_char;

	num = va_arg(ap, unsigned int);
	str = ft_utoa(num);
	len = ft_strlen(str);
	padding = get_padding_util(flags, len);
	pad_char = get_pad_char(flags);
	if (!flags.left_align)
		print_padding(get_full_pad(padding, num, flags), pad_char, size);
	if (flags.precision_specified && flags.precision > len)
		print_padding(flags.precision - len, '0', size);
	if (!(num == 0 && flags.precision == 0))
	{
		write(1, str, len);
		(*size) += len;
	}
	if (flags.left_align)
		print_padding(get_full_pad(padding, num, flags), ' ', size);
	free(str);
	++(*format);
}
