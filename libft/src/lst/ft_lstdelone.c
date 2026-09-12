#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(del)(lst->content);
	free(lst);
}

/* int main()
{
	t_list	*lst;

	lst = malloc(1 * sizeof(t_list));
	if (lst == NULL)
		return (1);
	lst->content = malloc(5 * sizeof(char));
	if (lst->content == NULL)
		return (free(lst), 1);
	ft_strlcpy(lst->content, "test", 5);
	lst->next = NULL;
	printf("before: %s\n", (char *)lst->content);
	ft_lstdelone(lst, free);
	printf("after: the node and its content are freed\n");
} */