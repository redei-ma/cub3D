#include "libft.h"

char	*ft_strdup(const char *src)
{
	char		*dest;
	size_t		len;

	len = ft_strlen(src);
	dest = (char *)malloc(len * sizeof (char) + 1);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (dest);
}

/* int main(void)
{
	char *src = "hello world";
	char *dest1 = ft_strdup(src);
	char *dest2 = strdup(src);
	printf("Reimplemented function: %s\n", dest1);
	printf("Original function: %s\n", dest2);
	free (dest1);
	free (dest2);
	return 0;
} */