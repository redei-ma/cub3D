#include "parsing.h"

static int	n_of_st_m(char const *s, char c, int *flag, int *j)
{
	int	count;

	*flag = 0;
	*j = 0;
	count = 0;
	if (*s == '\0')
		return (0);
	while (*(s + 1) != '\0')
	{
		if (*s != c && *(s + 1) == c)
			count++;
		s++;
	}
	if (*s != c && *(s + 1) == '\0')
		count++;
	return (count);
}

static char	**free_malloc_m(char **arr)
{
	int	j;

	j = 0;
	while (arr[j] != NULL)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

static char	*copy_word(char *arrst, char const *s, char c, int len)
{
	int	j;

	j = 0;
	while (s[j] != c && s[j] != '\0')
	{
		arrst[j] = s[j];
		j++;
	}
	while (j < len)
	{
		arrst[j] = ' ';
		j++;
	}
	arrst[j] = '\0';
	return (arrst);
}

static char	**malloc_line(char **arrst, int i, int len)
{
	arrst[i] = malloc((len + 1) * sizeof(char));
	if (arrst[i] == NULL)
	{
		arrst = free_malloc_m(arrst);
		return (arrst);
	}
	return (arrst);
}

/**
 * Splits the map into rows, padding every row to the same length
 *
 * @param s: the raw map, rows separated by c
 * @param c: the separator, a newline here
 * @param len: the length every row is padded to, with spaces
 * @param i: index to start from, reset to 0 on entry
 * @return a NULL-terminated array of rows, or NULL if an allocation failed
 *
 * This is not ft_split, and the padding is why it exists: maps are written
 * ragged, while the renderer and the flood fill both index the grid as a
 * rectangle. A space is the right filler because the subject counts spaces
 * as part of the map, and check_surrounded_by_wall already refuses any
 * walkable cell that touches one.
 */
char	**ft_split_len(char const *s, char c, int len, int i)
{
	char	**arrst;
	int		flag;
	int		j;

	i = 0;
	arrst = malloc((n_of_st_m(s, c, &flag, &j) + 1) * sizeof(char *));
	if (!arrst)
		return (NULL);
	while (s[j] != '\0')
	{
		if (s[j] != c && (flag == 1 || j == 0))
		{
			arrst = malloc_line(arrst, i, len);
			if (arrst == NULL)
				return (NULL);
			arrst[i] = copy_word(arrst[i], &s[j], c, len);
			i++;
			flag = 0;
		}
		if (s[j] == c)
			flag = 1;
		j++;
	}
	arrst[i] = NULL;
	return (arrst);
}
