#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		s_len;
	char	*str;
	char	cc;

	s_len = ft_strlen(s);
	str = (char *)s + s_len;
	cc = (unsigned char)c;
	while (s_len >= 0 && *str != cc)
	{
		s_len--;
		str--;
	}
	if (*str == cc)
		return (str);
	return (NULL);
}

/* int main ()
{
	int c = '\0';
	char *str = "";
	char *str1 = ft_strrchr(str, c);
	char *str2 = strrchr(str, c);

	printf("Reimplemented function: %s\n", str1);
	printf("Original function: %s\n", str2);
	return 0;
} */