#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	while (*big && len >= little_len)
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

/* int main()
{
	char big[] = "fd";
	char little[] = "xx";
	size_t len = 3;

	printf("Reimplemented function: %s\n", ft_strnstr(big, little, len));
	printf("Original function: %s\n", strnstr(big, little, len));
} */