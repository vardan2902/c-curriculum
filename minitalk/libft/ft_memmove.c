/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:46:08 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/09 15:35:53 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (!dst && !src)
		return (dst);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	if (dst_ptr > src_ptr && dst_ptr < src_ptr + len)
		while (len-- > 0)
			dst_ptr[len] = src_ptr[len];
	else
	{
		i = -1;
		while (++i < len)
			dst_ptr[i] = src_ptr[i];
	}
	return (dst);
}
