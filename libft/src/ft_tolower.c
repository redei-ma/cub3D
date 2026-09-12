#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

/* int main()
{
	char a = 90;
	char b = 100;
	printf("Reimplemented function: %d	%d\n", ft_tolower(a), ft_tolower(b));
	printf("Original function: %d	%d", tolower(a), tolower(b));
	return 0;
} */