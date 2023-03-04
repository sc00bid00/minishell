/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 12:53:15 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	imitate echo with -n option */
int	builtin_echo(t_cmd	*cmd)
{
	int		i;
	bool	option;

	i = 0;
	option = false;
	if (cmd->argc == 1)
		ft_putchar_fd('\n', 1);
	else if (cmd->argc >= 3 && ft_strncmp(cmd->arr[1], "-n", 3))
	{
		option = true;
		i++;
	}
	while (i < cmd->argc)
	{
		ft_putstr_fd(cmd->arr[i], 1);
		if (cmd->arr[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option == false)
		ft_putchar_fd('\n', 1);
	return (0);
}
