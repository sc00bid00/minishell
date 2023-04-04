/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:11:13 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 14:12:24 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpprexec(t_cmd *cmd, t_scmd *scmd)
{
	if (!ft_absrelpath(cmd))
		ft_paths(scmd);
	if (!cmd->path)
		cmd->stat |= CMD_KO;
}

void	ft_helpabsrelpath(DIR *dir, t_cmd *cmd)
{
	if (dir)
	{
		cmd->stat |= IS_DIR;
		closedir(dir);
	}
}

int	ft_absrelpath(t_cmd *cmd)
{
	DIR	*dir;

	dir = NULL;
	cmd->path = NULL;
	if (cmd->arr && ft_strchr(cmd->arr[0], '/'))
	{
		dir = opendir(cmd->arr[0]);
		ft_helpabsrelpath(dir, cmd);
		if (!access(cmd->arr[0], X_OK) && ft_strncmp(cmd->arr[0], "./", 2)
			&& ft_strncmp(cmd->arr[0], "../", 3))
		{
			cmd->stat |= EX_OK;
			cmd->path = ft_strdup(cmd->arr[0]);
		}
		else
		{
			cmd->stat |= (CMD_KO | SLASH);
		}
		if (cmd->stat & (IS_DIR | EX_OK))
			cmd->stat |= CMD_KO;
		return (1);
	}
	return (0);
}
