/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:47:48 by vapetros          #+#    #+#             */
/*   Updated: 2025/01/08 18:40:58 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated;

	if (count == 0 || size == 0)
		return (malloc(1));
	if (size > SIZE_MAX / count)
		return (NULL);
	allocated = malloc(count * size);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, size * count);
	return (allocated);
}
