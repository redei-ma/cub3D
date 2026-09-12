#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

/* int main()
{
	char a = 90;
	char b = 100;
	printf("Reimplemented function: %d	%d\n", ft_toupper(a), ft_toupper(b));
	printf("Original function: %d	%d", toupper(a), toupper(b));
	return 0;
} */
