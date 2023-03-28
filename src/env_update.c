/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:01:37 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/28 14:59:33 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* returns node previous to var, if prev does not exist, returns NULL */
t_env	*ret_prev_var(t_env **env, char *str)
{
	t_env	*temp;

	if (!str || !(*env))
		return (NULL);
	temp = (*env);
	while (temp && temp->next)
	{
		if (!ft_my_strcmp(temp->next->var_name, str))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/* returns var, if var does not exist, returns NULL */
t_env	*ret_var(t_env **env, char *str)
{
	t_env	*temp;

	if (!str || !(*env))
		return (NULL);
	temp = (*env);
	while (temp)
	{
		if (!ft_my_strcmp(temp->var_name, str))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/* update existing node with new variable content */
char	*upd_var(t_env **env, char *var, char *new_val)
{
	t_env	*temp;

	temp = ret_var(env, var);
	if (temp)
	{
		if (temp->var_content)
			free(temp->var_content);
		if (!new_val)
			temp->var_content = NULL;
		else
			temp->var_content = ft_strdup(new_val);
		return (temp->var_content);
	}
	return (NULL);
}

/* delete variable from list */
t_env	*del_var(t_env **env, char *var)
{
	t_env	*temp;
	t_env	*prev;

	temp = ret_var(env, var);
	prev = ret_prev_var(env, var);
	if (temp && prev)
	{
		prev->next = temp->next;
		free(temp->var_content);
		temp->var_content = NULL;
		free (temp->var_name);
		temp->var_name = NULL;
		free (temp);
	}
	return (*(env));
}
