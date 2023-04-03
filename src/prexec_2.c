/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:40:45 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/03 16:10:28 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpprexec(t_cmd *cmd, t_scmd *scmd)
{
	DIR	*dir;

	dir = NULL;
	if (cmd->path && cmd->arr && cmd->arr[0] && (cmd->arr[0][0] == '/'  || cmd->arr[0][0] == '.'))
			cmd->stat |= IS_DIR | CMD_KO;
	if (!cmd->path && cmd->arr && cmd->arr[0])
	{
		cmd->stat |= CMD_KO;
		if (cmd->arr)
			dir = opendir(cmd->arr[0]);
		ft_builtin(scmd);
		if ((!dir && !cmd->builtin) && (cmd->arr[0][0] == '/' || !ft_strncmp(cmd->arr[0], "./", 2) || !ft_strncmp(cmd->arr[0], "../", 3)))
		{
			scmd->dir = 1;
			ft_error(SHELL, cmd->arr[0], NULL, ERROR_1);
		}
	}
	if (dir)
		closedir(dir);
}
