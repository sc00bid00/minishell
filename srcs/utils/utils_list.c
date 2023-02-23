/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:05:21 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/23 14:39:38 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return last element of list */
t_env	*ms_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

/* add node to the end of the list */
t_env	*ms_lstadd_back(t_env *env, t_env *temp)
{
	t_env	*ptr;
	ptr = NULL;

	ptr = ms_lstlast(env);
	if (ptr)
		ptr->next = temp;
	else
		env = temp;
	return (env);
}

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*node;

// 	if (lst && del)
// 	{
// 		while (*lst)
// 		{
// 			node = *lst;
// 			*lst = node->next;
// 			del(node->content);
// 			free(node);
// 		}
// 	}
// }

// void	ft_lstdelone(t_list *lst, void (*del)(void *))
// {
// 	if (lst && lst->content && del)
// 	{
// 		del(lst->content);
// 		free(lst);
// 	}
// }

int	ms_lstsize(t_env *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/* joins two strings and a char */
char	*ms_multijoin(char const *s1, char c, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || ! s2)
		return (NULL);
	len = ft_strlen(s1) + 1 + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), &c, 1);
	ft_memcpy(str + ft_strlen(s1) + 1, s2, ft_strlen(s2));
	*(str + ft_strlen(s1) + 1 + ft_strlen(s2)) = '\0';
	return (str);
}