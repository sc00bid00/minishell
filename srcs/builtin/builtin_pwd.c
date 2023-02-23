/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:55:31 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/23 16:19:04 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	imitate behavior of pwd builtin */
void	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		write (1, "\n", 1);
	}
	else
	{
		ft_putendl_fd(pwd, 1);
		free (pwd);
	}
}
