#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	void	*cont;

	new = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		cont = f(lst->content);
		tmp = ft_lstnew(cont);
		if (!tmp)
		{
			del(cont);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}

/* void ft_deletecont(void *content)
{
	free(content);
}

void	*ft_lstchange(void *content)
{
	return(content += 1);
}

int main()
{
	t_list	*node = ft_lstnew(ft_strdup("i want to go home"));
	node -> next = ft_lstnew(ft_strdup("go home"));
	
	t_list *head = node;
	while(node)
	{
		printf("%s\n", (char *)node ->content);
		node = node -> next;
	}
	head = ft_lstmap(head, ft_lstchange, ft_deletecont);
	while(head)
	{
		printf("%s\n", (char *)head ->content);
		head = head -> next;
	}
} */