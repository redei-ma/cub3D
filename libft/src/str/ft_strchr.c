#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	cc;

	str = (char *)s;
	cc = (unsigned char)c;
	while (*str && *str != cc)
		str++;
	if (*str == cc)
		return (str);
	return (NULL);
}

/* int main ()
{
	int c = 'e';
	char *str = "teste";
	char *str1 = ft_strchr(str, 2048);
	char *str2 = strchr(str, 2048);

	printf("Reimplemented function: %s\n", str1);
	printf("Original function: %s\n", str2);
	return 0;
} */