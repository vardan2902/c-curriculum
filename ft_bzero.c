#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)b;
	while (n-- > 0)
		s[n] = 0;
}