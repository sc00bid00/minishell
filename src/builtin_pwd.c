/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:55:31 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 13:17:30 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	getcwd returns pointer to path if sucessful, else it returns NULL */
int	builtin_pwd(t_cmd *cmd, t_env *env)
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
		write (1, "\n", 1);
		return (EXIT_FAILURE);
	}
}
