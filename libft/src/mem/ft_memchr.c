#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	c = (unsigned char)c;
	while (n--)
	{
		if (*str == c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}

/* int main()
{
	char str[500] = "goodmorning";
	int c = 0;
	int	n = 20;
	char *result_ft = ft_memchr(str, c, n);
    char *result_orig = memchr(str, c, n);

	printf("Reimplemented function: %s\n", result_ft);
	printf("Original function: %s\n", result_orig);
	return 0;
} */