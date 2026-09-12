#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *niu)
{
	if (!lst || !niu)
		return ;
	niu -> next = *lst;
	*lst = niu;
}
