/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:01:37 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/06 17:34:34 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

/* returns var, if var does not exist, returns NULL */
t_env	*ret_var(t_env *env, char *str)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		if( ft_strlen(str) >= ft_strlen(temp->var_name))
		{
			if (!ft_strncmp(temp->var_name, str, ft_strlen(temp->var_name)))
				return (temp);
		}
		else
		{
			if (!ft_strncmp(temp->var_name, str, ft_strlen(str)))
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
t_env	*upd_var(t_env *env, char *var, char *new_val)
{
	t_env *temp;

	temp = ret_var(env, var);
	if (temp)
	{
		free(temp->var_content);
		temp->var_content = ft_strdup(new_val);
		return (temp);
	}
	return (NULL);
}

/* delete variable from list */
int	del_var(t_env *env, char *var)
{
	t_env *temp;

	temp = ret_var(env, var);
	if (temp)
	{
		free(temp->var_content);
		temp->var_content = NULL;
		free (temp->var_name);
		temp->var_name = NULL;
		temp = NULL;
		return (0);
	}
	return (1);
}
