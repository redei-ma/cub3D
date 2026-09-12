#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	size_t	tot;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(0));
	}
	tot = nmemb * size;
	if (tot / size != nmemb)
		return (NULL);
	dest = malloc(tot);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, tot);
	return (dest);
}

/* int     main()
{
	char	*s1;
	char	*s2;
    size_t	i = 0;
	size_t	j = 0;
	
    s1 = calloc(i, j);
	printf("Original function: %p\n", s1);
    s2 = ft_calloc(i, j);
    printf("Reimplemented function: %p\n", s2);
	printf("%zu", i);
    return (0);
} */
