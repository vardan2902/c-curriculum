/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:10:22 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/25 19:27:20 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_flags
{
	int	left_align;
	int	zero_pad;
	int	width;
	int	precision;
	int	precision_specified;
	int	alternate;
	int	space;
	int	plus;
}	t_flags;

typedef struct s_pad
{
	int		padding;
	char	pad_char;
}	t_pad;

int		parse_number(const char **format);
t_flags	extract_flags(const char **format);
void	print_padding(int len, char pad_char, int *size);
void	print_unsigned_decimal(va_list ap, t_flags flags, const char **format,
			int *size);
void	print_decimal(va_list ap, t_flags flags, const char **format,
			int *size);
void	print_char(va_list ap, t_flags flags, const char **format, int *size);
void	print_string(va_list ap, t_flags flags, const char **format, int *size);
void	print_hex(va_list ap, t_flags flags, const char **format, int *size);
void	print_pointer(va_list ap, t_flags flags, const char **format,
			int *size);
void	print_hex_alternate(const char **format, int *size);
int		ft_printf(const char *format, ...);
int		get_padding_util(t_flags flags, int len);
int		get_hex_pad_len(int padding, t_flags flags, int num);
int		should_print_alternate(int pos, t_flags flags, int num);
char	get_pad_char(t_flags flags);
void	print_sign(int is_negative, t_flags flags, int *size);
int		get_pad_len(t_flags flags, int num, int len, int is_negative);

#endif
