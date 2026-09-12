#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (size <= d_len)
		return (size + s_len);
	else
	{
		i = 0;
		while (src[i] != '\0' && (d_len + i) < size - 1)
		{
			dst[d_len + i] = src[i];
			i++;
		}
		dst[d_len + i] = '\0';
		return (d_len + s_len);
	}
}

/* int main()
{
	char src[] = "body asked you";
	char dest[] = "however, no";
	printf("Reimplemented function: %zu\n", ft_strlcat(dest, src, 0));
	//printf("Original function: %d", strlcat(dest, src, 10));
	return 0;	
} */