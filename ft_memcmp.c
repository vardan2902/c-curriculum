int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	while (s1_ptr[i] == s2_ptr[i] && i < n)
		++i;
	if (i == n)
		return (0);
	return (s1_ptr[i] - s2_ptr[i]);
}