/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:11:13 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/04 13:38:41 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	print environment list, with declare -x, sorted alphabetically */
int	print_export(t_env **env)
{
	if (env && !(*env)->next)
		return (EXIT_FAILURE);
	if ((*env)->next)
		(*env) = (*env)->next;
	while (env && (*env))
	{
		if ((*env)->var_name)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd((*env)->var_name, 1);
			if ((*env)->var_content)
				ft_putstr_fd("=", 1);
			else
				ft_putstr_fd("\n", 1);
		}
		if ((*env)->var_content)
			ft_putendl_fd((*env)->var_content, 1);
		if ((*env)->next)
			(*env) = (*env)->next;
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

/*	check if entered argument is valid, print error if not letter */
bool	is_valid_arg(char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[0] == '=' || str[0] == '\0')
	{
		ft_error (SHELL, "line 0: export: ", str, ERROR_4);
		g_exitstatus = 1;
		return (false);
	}
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || str[i] == '_' ))
		{
			ft_error (SHELL, "line 0: export: ", str, ERROR_4);
			g_exitstatus = 1;
			return (false);
		}
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
		free(name);
		free(value);
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
	char	*copy;

	check_redir(cmd);
	i = 1;
	if (cmd->arr && cmd->arr[1] == NULL)
	{
		print_export(env);
		g_exitstatus = 0;
	}
	while (cmd->arr && cmd->arr[i])
	{
		if (!ft_strncmp(&cmd->arr[i][0], "-", 1))
		{
			copy = ft_substr(cmd->arr[i], 0, 2);
			ft_error(SHELL, "line 0: export: ", copy, ERROR_10);
			ft_putendl_fd(ERROR_11, 2);
			g_exitstatus = 2;
			return (free (copy), 2);
		}
		if (is_valid_arg(cmd->arr[i]) == true)
			update_env(cmd->arr[i], env);
		i++;
	}
	return (g_exitstatus);
}
