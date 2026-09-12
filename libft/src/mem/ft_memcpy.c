#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

/* int main ()
{
	char dest1[50] = "destination";
	char dest2[50] = "destination";
	char src[50] = "source text";

	//ft_memcpy(dest1, src, 5);
	//memcpy(dest2, src, 5);
	//printf("Reimplemented function: %s\n", ft_memcpy(NULL, src, 5));
	printf("Original function: %s\n", memcpy(NULL, src, 5));
} */