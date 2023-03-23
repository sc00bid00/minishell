/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/23 18:05:57 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isvoption(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2))
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

/*	imitate echo with -n option */
int	builtin_echo(t_cmd	*cmd, t_env *env)
{
	int	i;
	int	option[2];

	(void)env;
	option[0] = 0;
	option[1] = 0;
	i = 1;
	if (cmd->arr && !cmd->arr[i])
		ft_putchar_fd('\n', 1);
	else if(cmd->arr && !ft_strncmp(cmd->arr[i], "$?", 3))
	{
		ft_putnbr_fd(exitstatus, 1);
		ft_putchar_fd('\n', 1);
		exitstatus = 0;
		return (EXIT_SUCCESS);
	}
	else if (cmd->arr && ft_isvoption(cmd->arr[i]))
	{
		option[0] = 1;
		option[1] = 1;
		i = 2;
	}
	while (cmd->arr && cmd->arr[i])
	{
		if (!ft_isvoption(cmd->arr[i]) && option[1])
			option[1] = 0;
		if (!option[1])
			ft_putstr_fd(cmd->arr[i], 1);
		if (cmd->arr[i + 1] && !option[1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!option[0])
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
