/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/23 12:12:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_checkoption(char *str)
{
	int	i;

	i = 0;
	if (str && !ft_strncmp(str, "-n", 2))
	{
		i++;
		while (str && str[i] == 'n')
			i++;
	}
	if ((size_t)i == ft_strlen(str))
		return (false);
	return (true);
}

/*	imitate echo with -n option */
int	builtin_echo(t_cmd	*cmd, t_env *env)
{
	int		i;
	bool	option;

	(void)env;
	if (cmd->arr && cmd->arr[1] == NULL)
		ft_putchar_fd('\n', 1);
	else if(cmd->arr && !ft_strncmp(cmd->arr[1], "$?", 3))
	{
		ft_putnbr_fd(exitstatus, 1);
		ft_putchar_fd('\n', 1);
		exitstatus = 0;
		return (EXIT_SUCCESS);
	}
	option = ft_checkoption(cmd->arr[1]);
	i = 1;
	if (!option)
		i = 2;
	while (cmd->arr && cmd->arr[i])
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
