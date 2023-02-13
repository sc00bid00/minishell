/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:17:18 by lsordo            #+#    #+#             */
/*   Updated: 2022/11/04 14:49:46 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlsth;
	t_list	*newlst;

	if (!lst)
		return (NULL);
	newlsth = ft_lstnew(f(lst->content));
	if (!newlsth)
	{
		free(newlsth);
		return (NULL);
	}
	lst = lst->next;
	while (lst && lst->content)
	{
		newlst = ft_lstnew(f(lst->content));
		if (!newlst)
		{
			ft_lstclear(&newlsth, del);
			return (NULL);
		}
		ft_lstadd_back(&newlsth, newlst);
		lst = lst->next;
	}
	return (newlsth);
}
