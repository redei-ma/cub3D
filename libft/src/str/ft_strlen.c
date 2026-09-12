#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0')
		n++;
	return (n);
}

/* int main(void)
{
	int i = ft_strlen("hello wor	ld");
	printf("%d", i);
} */