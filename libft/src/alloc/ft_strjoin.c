#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s1;
	unsigned int	len;
	char			*dest;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len = len_s1 + ft_strlen(s2) + 1;
	dest = ft_calloc(len, 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len_s1 + 1);
	ft_strlcat(dest, s2, len);
	return (dest);
}

/*int main()
{
	char *str1 = "Hello wor";
	char *str2 = "ld";
	char *dest = ft_strjoin(str1, str2);
	printf("New string: %s", dest);
	return 0;
} */
