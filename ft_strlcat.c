#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dest_len;
	unsigned int	src_len;

	i = -1;
	j = -1;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (!size || dest_len > size)
		return (dest_len + src_len);
	while (dest[++i])
		;
	while (src[++j] && j < size - dest_len - 1)
		dest[i++] = src[j];
	if (dest_len <= size)
		dest[i] = '\0';
	return (dest_len + src_len);
}