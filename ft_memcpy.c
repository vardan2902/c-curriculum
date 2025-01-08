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