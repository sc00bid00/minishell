/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:11:13 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 08:23:33 by lsordo           ###   ########.fr       */
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
int	update_env(int argc, char **argv, t_env *env)
{
	int		i;
	t_env	*temp;
	char	*value;
	char	*name;

	i = 1;
	while (argc > 1 && argv[i])
	{
		if (existing_var(env, argv[i]) == true)
		{
			value = get_var_content(argv[i]);
			name = get_var_name(argv[i]);
			upd_var(env, name, value);
		}
		else
		{
			temp = new_var(argv[i]);
			ms_lstadd_back(env, temp);
		}
		i++;
	}
	print_env(env, false);
	return (0);
}

/*	imitate behavior of export bash builtin */
int	builtin_export(int argc, char **argv, t_env *env)
{
	if (argc == 1)
	{
		print_env(env, true);
		return (0);
	}
	else
		update_env(argc, argv, env);
	return (0);
}
