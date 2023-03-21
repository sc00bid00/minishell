/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/21 09:45:30 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	imitate echo with -n option */
int	builtin_echo(t_cmd	*cmd, t_env *env)
{
	int		i;
	bool	option;

	(void)env;
	i = 1;
	option = false;
	if (cmd->arr && cmd->arr[1] == NULL)
		ft_putchar_fd('\n', 1);
	else if(cmd->arr && !ft_strncmp(cmd->arr[1], "$?", 3))
	{
		ft_putnbr_fd(exitstatus, 1);
		ft_putchar_fd('\n', 1);
		return (EXIT_SUCCESS);
	}
	else if(cmd->arr && !ft_strncmp(cmd->arr[1], "$?", 3))
	{
		ft_putnbr_fd(exitstatus, 1);
		ft_putchar_fd('\n', 1);
		return (EXIT_SUCCESS);
	}
	while (cmd->arr && cmd->arr[i] && !ft_strncmp(cmd->arr[i], "-n", 2))
		i++;
	if (i == 1)
		option = true;
	while (cmd->arr && cmd->arr[i])
	{
	{
		ft_putstr_fd(cmd->arr[i], 1);
		if (cmd->arr[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option == true)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
