/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:46:33 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/08 15:46:34 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	i = -1;
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	while (++i < n)
		dst_ptr[i] = src_ptr[i];
	return (dst);
}
