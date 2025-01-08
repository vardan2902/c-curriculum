#include "libft.h"

char	*ft_strdup(const char *src)
{
	unsigned int	len;
	unsigned int	i;
	char			*dest;

	len = ft_strlen(src);
	dest = (char *)malloc((len + 1) * sizeof (char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}