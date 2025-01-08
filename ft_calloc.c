#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	allocated = malloc(count * size);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, count * size);
	return (allocated);
}