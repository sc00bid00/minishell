/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:55:17 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/09 11:03:11 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpsubstitute(int flag, void *content, t_env *var)
{
	t_env	*env_var;

	if (!flag && content && ft_strchr((char *)content, '$'))
	{
		env_var = ret_var(var, &((char *)content)[1]);
		if (env_var)
		{
			free(content);
			if (env_var->var_content)
				content = ft_strdup(env_var->var_content);
		}
		else
		{
			free(content);
			content = NULL;
		}
	}
}

void	ft_substitute(t_list **lst, t_env *var)
{
	t_list	*tmp;
	int		flag;

	tmp = *lst;
	flag = 0;
	while (tmp)
	{
		if (ft_strchr((char *)tmp->content, '\''))
			flag ^= 1;
		ft_helpsubstitute(flag, tmp->content, var);
		tmp = tmp->next;
	}
}
