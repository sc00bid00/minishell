/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:55:31 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/28 14:04:15 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	getcwd returns pointer to path if sucessfull, else it returns failure */
int	builtin_pwd(t_cmd *cmd, t_env **env)
{
	char	*pwd;

	(void)cmd;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		free (pwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_error(SHELL, NULL, "pwd: ", NULL);
		free(pwd);
		g_exitstatus = errno;
		return (EXIT_FAILURE);
	}
}
