#include "parsing.h"

char	*ft_strjoin_m(char const *s1, char const *s2)
{
	char	*newst;
	int		i;

	i = 0;
	newst = malloc(ft_strlen_m(s1) + ft_strlen_m(s2) + 1);
	if (!newst)
		return (NULL);
	while (s1 && *s1 != '\0')
	{
		newst[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2 != '\0')
	{
		newst[i] = *s2;
		i++;
		s2++;
	}
	newst[i] = '\0';
	return (newst);
}
