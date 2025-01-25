/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:08:02 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/25 19:19:39 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_padding_util(t_flags flags, int len)
{
	int	padding;

	padding = 0;
	if (flags.width > len && flags.precision > len)
		padding = flags.width - flags.precision;
	else if (flags.width > len)
		padding = flags.width - len;
	return (padding);
}

int	get_hex_pad_len(int padding, t_flags flags, int num)
{
	if (flags.width && num == 0 && flags.precision == 0)
		padding += 1;
	if (flags.alternate && num != 0)
		padding -= 2;
	return (padding);
}

int	get_pad_len(t_flags flags, int num, int len, int is_negative)
{
	int	padding;

	padding = 0;
	if (flags.width > len && flags.precision >= len)
		padding = flags.width - flags.precision - is_negative;
	else if (flags.width > len)
		padding = flags.width - len;
	if (flags.width && !num && flags.precision == 0)
		padding += 1;
	if (num >= 0 && (flags.plus || flags.space))
		padding -= 1;
	return (padding);
}

int	should_print_alternate(int pos, t_flags flags, int num)
{
	if (pos == 0)
		return (flags.alternate && num && flags.zero_pad
			&& !flags.precision_specified);
	return (flags.alternate && num
		&& !(flags.zero_pad && !flags.precision_specified));
}

char	get_pad_char(t_flags flags)
{
	char	pad_char;

	pad_char = ' ';
	if (flags.zero_pad && !flags.precision_specified)
		pad_char = '0';
	return (pad_char);
}
