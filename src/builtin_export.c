/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:11:13 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/06 10:22:46 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	check if variable is already in env list*/
bool	existing_var(t_env *env, char *var)
{
	char	*name;

	name = get_var_name(var);
	if (name)
	{
		if (ret_var(env, name))
		{
			free (name);
			return (true);
		}
		else
		{
			free (name);
			return (false);
		}
	}
	return (false);
}

/*	either update existing or add new variable */
int	update_env(t_cmd *cmd, t_env *env)
{
	int		i;
	t_env	*temp;
	char	*value;
	char	*name;

	i = 0;
	while (cmd->argc > 1 && cmd->arr && cmd->arr[i])
	{
		if (existing_var(env, cmd->arr[i]) == true)
		{
			value = get_var_content(cmd->arr[i]);
			name = get_var_name(cmd->arr[i]);
			upd_var(env, name, value);
		}
		else
		{
			temp = new_var(cmd->arr[i]);
			ms_lstadd_back(env, temp);
		}
		i++;
	}
	// print_env(env, false);
	return (0);
}

/*	imitate behavior of export bash builtin */
int	builtin_export(t_cmd *cmd, t_env *env)
{
	if (cmd->argc == 1)
	{
		print_env(env, true);
		return (0);
	}
	else
		update_env(cmd, env);
	return (0);
}
