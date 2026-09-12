#include "libft.h"

char	**ft_free_char_mat(char **mat)
{
	int	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
	return (NULL);
}
