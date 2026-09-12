#include "libft.h"

void	**ft_free_mat(void **mat, int size)
{
	int	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (mat[i])
		{
			free(mat[i]);
			mat[i] = NULL;
		}
		i++;
	}
	free(mat);
	return (NULL);
}
