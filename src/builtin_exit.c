/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:37:51 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/20 16:50:40 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool is_numeric(char *str)
{
	int i;

	i = ft_atoi(str);
	if (i >= 0 && i <= 255)
		return (true);
	else
	{
		// ft_error("minishell: exit: ", str, ERROR_2);
		return (false);
	}
	return (false);
}

int builtin_exit(t_cmd *cmd, t_env *env)
{
	(void)env;

	// exitstatus = 
	if (cmd->arr && cmd->arr[1] == NULL)
		exitstatus = 0;
	else if (cmd->arr && !is_numeric(cmd->arr[1]))
	{
		ft_error("minishell: ", cmd->arr[0], ERROR_2);
		exitstatus = 255;
	}
	else if (cmd->arr && cmd->arr[2] == NULL)
	{
		if (is_numeric(cmd->arr[1]))
			exitstatus = ft_atoi(cmd->arr[1]);
		else
			ft_error("minishell: exit: ", cmd->arr[1], ERROR_2);
	}
	else if (cmd->arr && cmd->arr[2] != NULL)
	{
		ft_error("minishell: ", cmd->arr[0], ERROR_3);
		exitstatus = 350;
		return (EXIT_FAILURE);
	}
	printf("Exitstatus is:%d\n", exitstatus);
	// else if (cmd->)
	// ft_clean_env(env);
	return (exitstatus);
}
