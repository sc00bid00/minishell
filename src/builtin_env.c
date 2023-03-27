/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:50:57 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 17:19:29 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	print environment list, if called from export builtin, with declare -x */
int	print_env(t_env **env, bool ex)
{
	if (env && !(*env)->next)
	{
		ft_error("minishell: env: ", NULL, ERROR_5);
		return (EXIT_FAILURE);
	}
	if ((*env)->next)
		(*env) = (*env)->next;
	while (env && (*env))
	{
		if ((*env)->var_name)
		{
			if (ex)
				ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd((*env)->var_name, STDOUT_FILENO);
			if ((*env)->var_content)
				ft_putstr_fd("=", STDOUT_FILENO);
			else
				ft_putstr_fd("\n", STDOUT_FILENO);
		}
		if ((*env)->var_content)
			ft_putendl_fd((*env)->var_content, STDOUT_FILENO);
		if ((*env)->next)
			(*env) = (*env)->next;
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

/*	imitate behavior of env */
int	builtin_env(t_cmd *cmd, t_env **env)
{
	if (cmd->arr[1] != NULL)
	{
		ft_error("env: ", cmd->arr[1], ERROR_1);
		g_exitstatus = 127;
		return (EXIT_FAILURE);
	}
	if (!print_env(env, false))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
