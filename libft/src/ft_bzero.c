#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/* int main()
{
    char str1[50] = "Hello world!";
    char str2[50] = "Hello world!";

    bzero(str1, 6);
    ft_bzero(str2, 6);
    printf("Original function:\n%s\n", str1);
    printf("Reimplemented function:\n%s", str2);

    return 0;
} */