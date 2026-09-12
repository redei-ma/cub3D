#include "libft.h"

void	safe_close(int *fd)
{
	if (!fd)
		return ;
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}
