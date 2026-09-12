#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* // Function that converts a character to uppercase
void to_upper(unsigned int i, char *c)
{
    *c = (char)toupper((unsigned char)*c);
}

int main()
{
    char str[] = "hello world";

    // Apply to_upper to every character of the string
    ft_striteri(str, to_upper);

    printf("%s\n", str);  // prints "HELLO WORLD"
    return 0;
} */
