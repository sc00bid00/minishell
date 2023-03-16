/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/16 12:48:13 by kczichow         ###   ########.fr       */
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
	// printf("TEST\n");
	// while (cmd->arr[i])
	// {
	// 	printf("arr at %d is %s\n",i, cmd->arr[i]);
	// 	i++;
	// }
	option = false;
	if (cmd->arr && cmd->arr[1] == NULL)
		ft_putchar_fd('\n', 1);
	while (cmd->arr && cmd->arr[i] && !ft_strncmp(cmd->arr[i], "-n", 2))
		i++;
	if (i == 1)
		option = true;
	while (cmd->arr && cmd->arr[i])
	{	
		ft_putstr_fd(cmd->arr[i], 1);
		if (cmd->arr[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option == true)
		ft_putchar_fd('\n', 1);
	return (0);
}
