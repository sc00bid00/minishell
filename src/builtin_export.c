/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:11:13 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 10:25:28 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_valid_arg(char c, bool first)
{
	if (first)
	{
		if (ft_isalpha(c) || c == '_' )
			return (true);
		else
			return (false);
	}
	else
	{
		if (ft_isdigit(c) || ft_isalpha(c) || c == '_')
			return (true);
	}
	return (false);
}

/*	extract and return variable name from envp */
char	*get_var_name_export(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	if (is_valid_arg(var[0], true))
		i++;
	else
	{
		ft_error("minishell: export: ", var, ERROR_4);
		return (NULL);
	}
	while (var[i] && var[i] != '=')
	{
		if (is_valid_arg(var[0], false))
			i++;
		else
		{
			ft_error("minishell: export: ", var, ERROR_4);
			return (NULL);
		}
	}
	var_name = ft_substr(var, 0, i);
	printf("var_name is: %s\n", var_name);
	return (var_name);
}

/*	check if variable is already in env list*/
bool	existing_var(t_env *env, char *var)
{
	char	*name;

	name = get_var_name_export(var);
	if (name)
	{
		if (ret_var(env, name))
		{
			free (name);
			printf("true\n");
			return (true);
		}
		else
			free (name);
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

	i = 1;
	while (cmd->arr && cmd->arr[i])
	{
		if (existing_var(env, cmd->arr[i]) == true)
		{
			name = get_var_name_export(cmd->arr[i]);
			value = get_var_content(cmd->arr[i]);
			if (value)
				upd_var(env, name, value);
		}
		else
		{
			temp = new_var(cmd->arr[i], true);
			ms_lstadd_back(env, temp);
		}
		i++;
	}
	return (0);
}

/*	imitate behavior of export bash builtin */
int	builtin_export(t_cmd *cmd, t_env *env)
{
	if (cmd->arr && cmd->arr[1] == NULL)
	{
		print_env(env, true);
		return (0);
	}
	else
		update_env(cmd, env);
	return (0);
}
