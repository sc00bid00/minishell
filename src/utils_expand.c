/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 09:05:02 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/08 16:44:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_explode(t_list **lst, char *str)
{
	int		p[2];
	char	*tmp;

	p[0] = 0;
	p[1] = 0;
	while (str && str[p[1]])
	{
		if (p[1] && (str[p[1]] == '$' || str[p[1]] == '"'))
		{
			tmp = ft_substr(str, p[0], p[1] - p[0]);
			ft_lstadd_back(lst, ft_lstnew(tmp));
			p[0] = p[1];
		}
		p[1]++;
	}
	if (p[1] - p[0] > 1)
	{
		tmp = ft_substr(str, p[0], p[1] - p[0]);
		ft_lstadd_back(lst, ft_lstnew(tmp));
	}
}

void	ft_substitute(t_list **lst, t_env *var)
{
	t_list	*tmp;
	t_env	*env_var;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->content && ft_strchr((char *)tmp->content, '$'))
		{
			env_var = ret_var(var, &((char *)tmp->content)[1]);
			if (env_var && env_var->var_content)
			{
				free(tmp->content);
				tmp->content = ft_strdup(env_var->var_content);
			}
		}
		tmp = tmp->next;
	}
}

static int	ft_len(t_list *lst)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
			len += ft_strlen((char *)tmp->content);
		tmp = tmp->next;
	}
	return (len);
}

void	ft_reassemble(t_list *lst, t_list *node)
{
	t_list	*tmp;
	int		i;

	i = 0;
	i = ft_len(lst);
	if (!i)
		return ;
	free(node->content);
	node->content = ft_calloc(i + 1, 1);
	if (!node->content)
		exit(1);
	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->content)
		{
			ft_memcpy(&((char *)node->content)[i], (char *)tmp->content, \
				ft_strlen((char *)tmp->content));
			i += ft_strlen((char *)tmp->content);
		}
		tmp = tmp->next;
	}
}
