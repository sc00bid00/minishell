/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:57:28 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/11 14:57:51 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(char *s1, char *s2, int i)
{
	char *str;

	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd (s2, 2);
	ft_putstr_fd(": ", 2);
	if (i == 0)
		str = strerror(errno);
	else
		str = "meine Fehlermeldung";
	ft_putstr_fd(str, 2);
}

void	ft_eerr(t_cmd *cmd, int err, void *message, void *name)
{
	ft_putstr_fd((char *)message, STDERR_FILENO);
	ft_putendl_fd((char *)name, STDERR_FILENO);
	cmd->err_flag = err;
}
