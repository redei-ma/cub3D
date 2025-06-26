
#include "parsing.h"

// cerca quante stringhe vanno create
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
	while(j < len)
	{
		arrst[j] = ' ';
		j++;
	}
	arrst[j] = '\0';
	return (arrst);
}

char    **malloc_line(char **arrst, int i, int len)
{
	arrst[i] = malloc((len + 1) * sizeof(char));
	if (arrst[i] == NULL)
	{
		arrst = free_malloc_m(arrst);
		return (arrst);
	}
	return (arrst);
}

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
