#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen(src);
	i = -1;
	if (!size)
		return (len);
	while (++i < size - 1 && src[i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (len);
}