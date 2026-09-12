#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/* int main(void)
{
	int i = ft_isdigit('z');
	printf("%d", i);
} */