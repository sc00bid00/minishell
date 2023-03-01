/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/01 16:32:22 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	imitate echo with -n option */
int	builtin_echo(int argc, char **argv, t_env *env)
{
	int		i;
	bool	option;

	(void) env;
	i = 1;
	option = false;
	if (argc == 1)
		ft_putchar_fd('\n', 1);
	else if (argc >= 3 && ft_strncmp(argv[2], "-n", 3))
	{
		option = true;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option == false)
		ft_putchar_fd('\n', 1);
	return (0);
}
