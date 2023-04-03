/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:14:18 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/03 14:37:51 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpexptilde_1(t_token *tkn, t_list *lst)
{
	t_env	*env_var;
	char	*tmp;

	tmp = NULL;
	if (((char *)lst->content)[1] == '/')
	{
		env_var = ret_var(&tkn->env, "HOME");
		if (env_var && env_var->var_content)
		{
			tmp = ft_strjoin(env_var->var_content, &((char *)lst->content)[1]);
			free(lst->content);
			lst->content = tmp;
		}
	}
}

void	ft_exptilde(t_token *tkn)
{
	t_list	*lst;
	t_env	*env_var;
	int		i;

	lst = tkn->lst;
	i = 0;
	while (lst)
	{
		if (i < 3 && lst->content && ft_strchr((char *)lst->content, '~')
			&& ft_strlen((char *)lst->content) > 1)
			ft_helpexptilde_1(tkn, lst);
		else if (i < 3 && lst->content
			&& !ft_strncmp((char *)lst->content, "~", 1))
		{
			env_var = ret_var(&tkn->env, "HOME");
			if (env_var && env_var->var_content)
			{
				free(lst->content);
				lst->content = ft_strdup(env_var->var_content);
			}
		}
		i++;
		lst = lst->next;
	}
}
