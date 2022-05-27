#include "parsing.h"

t_dlist	*dlstnew(void *content)
{
	t_dlist *lst;

	lst = malloc(sizeof(t_dlist));
	if (!lst)
		return (0);
	lst->next = lst;
	lst->prev = lst;
	lst->content = content;
	return (lst);
}

void	dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*tmp;

	if (!(*lst))
		*lst = new;
	else
	{
		tmp = (*lst)->prev;
		tmp->next = new;
		new->prev = tmp;
		new->next = (*lst);
		(*lst)->prev = new;
	}
}

void	dlst_free(t_dlist **lst)
{
	t_dlist	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
		tmp = 0;
	}
}