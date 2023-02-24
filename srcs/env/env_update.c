/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:01:37 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/24 15:09:38 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* three variables need to be updated, pwd, old pwd, shell level */
char	*return_var_content(t_env *env, char *str)
{
	t_env *temp;
	
	temp = env;
	while (temp->next)
	{
		if (!ft_strncmp(temp->var_name, str, strlen(str)))
			return (temp->var_content);
		temp = temp->next;
	}
	return (NULL);
}

/* update existing node with new variable content */
t_env	*update_variable(t_env *env, char *var, char *new_val)
{
	t_env *temp;
	temp = env;
	
	while (temp->next)
	{
		if (!ft_strncmp(temp->var_name, var, ft_strlen(var)))
		{
			free(temp->var_content);
			temp->var_content = ft_strdup(new_val);
				return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_env	*delete_variable(t_env *env, char *str)
{
	return (NULL);
}

t_env	*add_variable(t_env *env, char *str)
{
	return (NULL);
}
