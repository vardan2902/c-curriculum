#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*s_ptr;

	s_ptr = (unsigned char *)s;
	i = -1;
	while (++i < n)
		if (s_ptr[i] == (unsigned char)c)
			return (&s_ptr[i]);
	if (s_ptr[i] == (unsigned char)c)
		return (&s_ptr[i]);
	return (NULL);
}
