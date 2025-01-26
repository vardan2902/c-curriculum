/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:38:20 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/08 15:38:47 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int c)
{
	if (c < 0)
		return (-c);
	return (c);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
		ft_putchar_fd('-', fd);
	c = ft_abs(n % 10) + 48;
	n = ft_abs(n / 10);
	if (n != 0)
		ft_putnbr_fd(n, fd);
	ft_putchar_fd(c, fd);
}
