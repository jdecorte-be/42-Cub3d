/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:41:54 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/26 11:16:35 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = content;
	list->next = NULL;
	return (list);
}

t_dlist	*dlstnew(void *content)
{
	t_dlist	*lst;

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
	t_dlist	*tf;

	if (*lst == 0)
		return ;
	tmp = (*lst)->next;
	(*lst)->next = 0;
	while (tmp)
	{
		free(tmp->content);
		tf = tmp;
		tmp = tmp->next;
		free(tf);
	}
}
