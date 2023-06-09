/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:42:29 by lsordo          #+#    #+#             */
/*   Updated: 2023/04/03 13:42:30 by lsordo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_lsttoarr(t_list *lst)
{
	int		size;
	int		i;
	char	**arr;
	t_list	*tmp;

	size = ft_lstsize(lst);
	tmp = lst;
	arr = ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		exit(EXIT_FAILURE);
	i = 0;
	while (tmp)
	{
		arr[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	return (arr);
}

void	ft_echoadjarr(t_list *lst, char ***arr)
{
	ft_freesplit(*arr);
	*arr = ft_lsttoarr(lst);
}

int	ft_isdquote(char *str)
{
	if (!ft_strncmp(str, "\"\"", 3) || !ft_strncmp(str, "\'\'", 3))
		return (1);
	return (0);
}

int	ft_isredtoken(char *str)
{
	if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1)
		|| !ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2)
		|| !ft_strncmp(str, "|", 1))
		return (1);
	else
		return (0);
}

void	ft_rmred(t_list **lst)
{
	t_list	*tmp;
	t_list	*new;
	int		flag;

	tmp = *lst;
	new = NULL;
	flag = 0;
	ft_helprmed(tmp, &new, &flag);
	ft_cleanlst(*lst);
	*lst = new;
}
