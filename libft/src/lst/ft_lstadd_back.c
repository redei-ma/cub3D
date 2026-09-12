#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *niu)
{
	t_list	*last;

	if (!lst || !niu)
		return ;
	if (!*lst)
	{
		*lst = niu;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = niu;
}

/* int	main ()
{
	
} */