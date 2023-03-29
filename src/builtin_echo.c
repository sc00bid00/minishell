/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/29 11:21:41 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isvoption(char *str)
{
	int	i;

	if (str && ft_strncmp(str, "-n", 2))
		return (0);
	i = 1;
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmd, t_env **env)
{
	int	i;
	int	optn;

	(void)env;
	optn = 0;
	i = 1;
	if (cmd->arr && !cmd->arr[i])
		ft_putchar_fd('\n', 1);
	else if (cmd->arr && !ft_strncmp(cmd->arr[i], "$?", 3))
	{
		ft_putnbr_fd(g_exitstatus, 1);
		ft_putchar_fd('\n', 1);
		g_exitstatus = 0;
		return (EXIT_SUCCESS);
	}
	while (cmd->arr && cmd->arr[i] && ft_isvoption(cmd->arr[i]))
	{
		optn = 1;
		i++;
	}
	while (cmd->arr && cmd->arr[i])
	{
		ft_putstr_fd(cmd->arr[i], 1);
		if (cmd->arr[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!optn)
		ft_putchar_fd('\n', 1);
	g_exitstatus = 0;
	return (EXIT_SUCCESS);
}
