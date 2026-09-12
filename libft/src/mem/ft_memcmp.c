#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n && *str1 == *str2)
	{
		str1++;
		str2++;
		n--;
	}
	if (n)
		return (*str1 - *str2);
	return (0);
}

/* int main()
{
	int s1[] = {1, 0, 11, 5};	
	int s2[] = {1, 0, 11, 84};
	int	n = 50;

	printf("Reimplemented function: %d\n", ft_memcmp(s1, s2, n));
	printf("Original function: %d\n", memcmp(s1, s2, n));
	return 0;
} */