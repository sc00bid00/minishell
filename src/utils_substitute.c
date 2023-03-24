/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:55:17 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/24 12:14:45 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_substdollar(t_list **lst, t_env *var)
{
	t_env	*env_var;
	char	*tmp;

	env_var = ret_var(var, &((char *)(*lst)->content)[1]);
	if (env_var)
	{
		if (env_var->var_content)
		{
			free((*lst)->content);
			(*lst)->content = ft_strdup(env_var->var_content);
		}
	}
	else if ((*lst)->next && (*lst)->next->content
		&& ft_isdigit(((char *)(*lst)->next->content)[0]))
	{
		tmp = ft_strdup(&((char *)(*lst)->next->content)[1]);
		free((*lst)->next->content);
		(*lst)->next->content = tmp;
	}
}

void	ft_substtilde(t_list **lst, t_env *var)
{
	t_env	*env_var;

	free((*lst)->content);
	if (!(*lst)->next
		|| ((*lst)->next && (*lst)->next->content
			&& !ft_strncmp((*lst)->next->content, "/", 1)))
	{
		env_var = ret_var(var, "HOME");
		(*lst)->content = ft_strdup(env_var->var_content);
	}
	else
		(*lst)->content = ft_strdup("~");
}

void	ft_substitute(t_list **lst, t_env *var)
{
	t_list	*tmp;
	int		flag;
	char	*content;
	int		i;

	tmp = *lst;
	flag = 0;
	i = 0;
	while (tmp)
	{
		content = (char *)tmp->content;
		if (ft_strchr(content, '\''))
			flag ^= 1;
		if (!flag && content && ft_strchr(content, '$'))
			ft_substdollar(&tmp, var);
		else if (!i && !flag && content && !ft_strncmp(content, "~", 1))
			ft_substtilde(&tmp, var);
		tmp = tmp->next;
		i++;
	}
}
