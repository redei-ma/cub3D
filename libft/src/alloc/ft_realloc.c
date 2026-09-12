#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_calloc(new_size, 1));
	if (new_size == old_size)
		return (ptr);
	new_ptr = ft_calloc(new_size, 1);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (new_size > old_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free (ptr);
	return (new_ptr);
}

/* int main ()
{
	char *buf = ft_calloc(10, 1);
	buf[0] = 'c';
	buf[1] = 'b';
	printf("%s\n", buf);
	buf = ft_realloc(buf, 10, 3);
	printf("%s\n", buf);
} */
