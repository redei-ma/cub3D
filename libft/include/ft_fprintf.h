#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include "libft.h"


int		ft_putchard(char c, int fd);
size_t	ft_putstrd(char *s, int fd);
int		ft_putnbrd(long long n, int fd);
int		ft_puthexd(long long n, char c, int fd);
int		ft_putptrd(unsigned long long n, int fd);

#endif
