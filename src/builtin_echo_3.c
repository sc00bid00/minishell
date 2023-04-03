/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:44:22 by lsordo          #+#    #+#             */
/*   Updated: 2023/04/03 13:45:52 by lsordo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* extract from ft_spoilecho to comly with norminette max 25 lines */
void	ft_spoilecho_util(t_list *tmp)
{
	char	*str;

	while (tmp)
	{
		if (((char *)tmp->content)[0] == '\'')
			str = ft_strtrim((char *)tmp->content, "\'");
		else if (((char *)tmp->content)[0] == '\"')
			str = ft_strtrim((char *)tmp->content, "\"");
		else
			str = ft_strdup((char *)tmp->content);
		free((tmp)->content);
		tmp->content = str;
		tmp = tmp->next;
	}
}

void	ft_spoilecho(t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	while (*lst && ft_isdquote((*lst)->content))
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	tmp = *lst;
	while (tmp && tmp->next)
	{
		while (tmp && tmp->next && ft_isdquote(tmp->next->content))
		{
			tmp2 = tmp->next->next;
			free(tmp->next->content);
			free(tmp->next);
			tmp->next = tmp2;
		}
		tmp = tmp->next;
	}
	tmp = *lst;
	ft_spoilecho_util(tmp);
}

int	ft_isvoption(char *str)
{
	int	i;

	i = 0;
	if (str && (ft_strncmp(str, "-n", 2) && str[i] != ' '))
		return (0);
	if (!ft_strncmp(str, "-n", 2))
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			if (str[i] == ' ')
				break ;
			i++;
		}
	}
	else if (!ft_allspaces(str))
		return (0);
	return (1);
}

/* splits the string according to $ to send to expansion */
t_list	*ft_strtolstecho(char *str)
{
	t_list	*lst;
	int		i;
	int		j;

	lst = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, i - j)));
			j = i;
		}
		i++;
	}
	if (i != j)
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, i - j)));
	return (lst);
}

void	ft_remspcnul(t_list **lst)
{
	t_list	*tmp;
	t_list	*new;

	new = NULL;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && !ft_strncmp(tmp->content, " ", 2)
			&& ((char *)tmp->next->content)[0] == '\0')
			tmp = tmp->next;
		else
			ft_lstadd_back(&new, ft_lstnew(ft_strdup(tmp->content)));
		tmp = tmp->next;
	}
	ft_cleanlst(*lst);
	*lst = new;
}
