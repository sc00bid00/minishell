/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:01:37 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 17:05:21 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* returns var, if var does not exist, returns NULL */
t_env	*ret_var(t_env **env, char *str)
{
	t_env	*temp;

	if (str == NULL)
		return (NULL);
	temp = (*env);
	while (temp)
	{
		if (ft_strlen(str) <= ft_strlen(temp->var_name))
		{
			if (!ft_strncmp(temp->var_name, str, ft_strlen(temp->var_name) + 1))
				return (temp);
		}
		else
		{
			if (!ft_strncmp(temp->var_name, str, ft_strlen(str) + 1))
				return (temp);
		}
		if (temp->next)
			temp = temp->next;
		else
			return (NULL);
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
	else
		return (NULL);
	return (NULL);
}

/* delete variable from list */
int	del_var(t_env **env, char *var)
{
	t_env	*temp;

	temp = ret_var(env, var);
	if (temp)
	{
		free(temp->var_content);
		temp->var_content = NULL;
		free (temp->var_name);
		temp->var_name = NULL;
		temp = NULL;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	del_first_var(t_env **env)
{
	t_env	*temp;

	temp = (*env)->next;
	printf("var_content = %s\n", (*env)->var_content);
	free ((*env)->var_content);
	printf("var_name = %s\n", (*env)->var_name);
	free ((*env)->var_name);
	free (*env);
	*env = temp;
}
