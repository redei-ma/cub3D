#include "libft.h"

/*
Stricter atoi: returns 0 if the number is out of the int range or if the
string holds anything that is not a number, like "15d7" or a leading space.
Use ft_atoi for the standard behaviour.
*/
int	ft_natoi(char *str)
{
	int		i;
	int		sign;
	long	n;

	if (!str)
		return (0);
	i = 0;
	n = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	n = sign * n;
	if (n < INT_MIN || n > INT_MAX || str[i] != '\0')
		n = 0;
	return (n);
}

/* int main(void)
{
	char	*cases[] = {"  42", "42", "15d7", "2147483648", "-42"};
	int		i;

	i = 0;
	while (i < 5)
	{
		printf("%-12s ft_atoi: %-12d ft_natoi: %d\n",
			cases[i], ft_atoi(cases[i]), ft_natoi(cases[i]));
		i++;
	}
} */
