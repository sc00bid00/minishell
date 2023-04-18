/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:55:31 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/03 11:11:12 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	getcwd returns pointer to path if sucessfull, else it returns failure */
int	builtin_pwd(t_cmd *cmd, t_env **env)
{
	char	*pwd;

	(void)cmd;
	(void)env;
	if (cmd->stat & FILE_KO)
		ft_fileissues(cmd->scmd);
	if (cmd->stat & RED_OK)
		ft_redirect(cmd->scmd);
	ft_noredirect(cmd->scmd);
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
