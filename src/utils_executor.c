/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:17:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/03 13:40:45 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell.h>
#include <minishell.h>

int	ft_helpexecutor(t_scmd *scmd)
{
	close(scmd->fd[0]);
	if (!ft_pipein(scmd))
		return (0);
	if (!ft_firstcmd(scmd))
		return (0);
	return (1);
}
