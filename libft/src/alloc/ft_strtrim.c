#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*dest;

	if (!s1)
		return (NULL);
	if (!set || !ft_strlen(s1))
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start >= end)
		return (ft_calloc(1, 1));
	while (s1[end] && ft_strchr(set, s1[end]))
		end--;
	dest = ft_substr(s1, start, end - start + 1);
	return (dest);
}

/* int	main()
{
	char	str[] = "  \t \t \n  gfdg \n\n\n\t";
	char	set[] = " \n\t";
	char 	*dest = ft_strtrim(str, set);
	printf("%s", dest);
} */
