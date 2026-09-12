#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

/* int main()
{
	char dest1[50] = "destination";
	//char dest2[50] = "destination";
	char src[50] = "source text ";

	size_t a = ft_strlcpy(dest1, src, 5);
	//size_t b = strlcpy(dest2, src, 5);
	printf("Reimplemented function: %zu\n", a);
	//printf("Original function: %zu\n", b);
} */