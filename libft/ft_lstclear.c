/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:57:03 by mgourlai          #+#    #+#             */
/*   Updated: 2023/04/25 21:57:04 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
/*
int	main(void)
{
	t_list	*node;
	t_list	*list;
	int	i;
	
	i = 0;
	list = ft_lstnew(NULL);
	while (i < 10)
	{
		node = ft_lstnew(NULL);
		ft_lstadd_back(&list, node);
		++i;
	}
	while (list != NULL)
	{
		printf("%p\n", list->content);
		list = list->next;
	}
}

int	min(int arr[], int len)
{
	int	i;
	int	m;
	
	if (len == 1)
		return (arr[0]);
	i = 1;
	m = arr[0];
	while (i < len)
	{
		if (arr[i] < m)
			m = arr[i];
		++i;
	}
	return (m);

}*/
