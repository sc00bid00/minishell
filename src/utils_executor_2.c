/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:52:37 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 13:52:56 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpcmdissues(t_cmd *cmd, t_scmd *scmd)
{
	if (cmd->stat & IN_OK)
		close(cmd->fd_in);
	if (cmd->stat & OUT_OK)
		close(cmd->fd_out);
	close(scmd->fd[0]);
	close(scmd->fd[1]);
}
