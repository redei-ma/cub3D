#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n--)
	{
		*temp = c;
		temp++;
	}
	return (s);
}

/* int main()
{
	char str1[50] = "Hello world!";
	char str2[50] = "Hello world!";

	memset(str1, 'X', 6);
	ft_memset(str2, 'X', 6);
	printf("Original function:\n%s\n", str1);
	printf("Reimplemented function:\n%s", str2);
} */