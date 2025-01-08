#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	i = -1;

	if (dst_ptr > src_ptr && dst_ptr < src_ptr + len)
		while (len-- > 0)
			dst_ptr[len] = src_ptr[len];
	else
		while (++i < len)
			dst_ptr[i] = src_ptr[i];
	return (dst);
}