/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:11:13 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 11:33:32 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	check if entered argument is valid, print error if not letter */
bool	is_valid_arg(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	if (!ft_isalpha(str[0]))
	{
		ft_error("minishell: export: ", str, ERROR_4);
		return (false);
	}
	while (str[i] != 0 && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' ))
			return (false);
		i++;
	}
	return (true);
}

/*	check if variable is already in env list*/
bool	existing_var(t_env **env, char *var)
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
			free (name);
	}
	return (false);
}

/*	either update existing or add new variable */
void	update_env(char *str, t_env **env)
{
	t_env	*temp;
	char	*value;
	char	*name;

	if (existing_var(env, str) == true)
	{
		name = get_var_name(str);
		value = get_var_content(str);
		upd_var(env, name, value);
	}
	else
	{
		temp = new_var(str);
		(*env) = ms_lstadd_back(*env, temp);
	}
}

/*	imitate behavior of export bash builtin: if no arguments, printf env */
int	builtin_export(t_cmd *cmd, t_env **env)
{
	size_t	i;

	i = 1;
	if (cmd->arr && cmd->arr[1] == NULL)
	{
		print_env(env, true);
		exitstatus = 0;
	}
	while (cmd->arr && cmd->arr[i])
	{
		if (is_valid_arg(cmd->arr[i]))
			update_env(cmd->arr[i], env);
		i++;
	}
	return (0);
}
