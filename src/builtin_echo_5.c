/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:58:33 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 09:59:09 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_splitlist_util(t_list **copylst, t_list *lst, int j)
{
	if (!ft_strncmp((char *)lst->content, " ", 2) && j == 0
		&& lst->next && !ft_strncmp((char *)lst->next->content, "echo", 5))
				;
	else if (lst->content && ((char *)lst->content)[0] == '\0')
	{
		if (lst->next && !ft_strncmp(lst->next->content, " ", 2))
			lst = lst->next;
	}
	else if (ft_allspaces((char *)lst->content))
		ft_lstadd_back(copylst, ft_lstnew(ft_strdup(" ")));
	else
		ft_lstadd_back(copylst, ft_lstnew(ft_strdup(lst->content)));
}

void	ft_helpsplitlist(t_list *lst, int j, t_list **copylst)
{
	while (lst && ft_strncmp(lst->content, "|", 2))
	{
		if (j == 0 && !ft_strncmp(lst->content, " ", 2))
			lst = lst->next;
		else if (lst->next && !ft_strncmp(lst->next->content, "|", 2)
			&& !ft_strncmp(lst->content, " ", 2))
			lst = lst->next;
		else
		{
			ft_splitlist_util(&(*copylst), lst, j);
			j++;
			lst = lst->next;
		}
	}
}
