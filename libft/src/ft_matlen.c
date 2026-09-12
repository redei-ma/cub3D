#include "libft.h"

int	ft_matlen(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
		i++;
	return (i);
}
