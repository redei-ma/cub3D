#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n && *ss1 && *ss2 && *ss1 == *ss2)
	{
		ss1++;
		ss2++;
		n--;
	}
	if (n)
		return (*ss1 - *ss2);
	return (0);
}

/* int main()
{
	char *s1 = "abcdef";	
	char *s2 = "abc\xfdxx";
	int	n = 19;

	printf("Reimplemented function: %d\n", ft_strncmp(s1, s2, n));
	printf("Original function: %d\n", strncmp(s1, s2, n));
	return 0;
} */