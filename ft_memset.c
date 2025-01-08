#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)b;
	while (len-- > 0)
		byte_ptr[len] = (unsigned char)c;
	return (b);
}