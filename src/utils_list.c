/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:05:21 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 16:18:35 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	ft_ms_lstclear(t_env *lst)
{
	t_env	*node;

	if (lst && lst->next)
	{
		while (lst)
		{
			node = lst;
			lst = node->next;
			// ft_ms_lstdelone(node);
			free(node);
			// lst = node;
		}
	}
	lst = NULL;
}

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

/*	clean up environment */
void	ft_cleanenv(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while ((*env) && (*env)->next)
	{
		if ((*env)->var_name)
			free((*env)->var_name);
		if ((*env)->var_content)
			free ((*env)->var_content);
		tmp =(*env);
		(*env) = (*env)->next;
		free(tmp);
	}
}