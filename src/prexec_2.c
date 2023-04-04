/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:11:13 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 18:26:31 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpprexec(t_cmd *cmd, t_scmd *scmd)
{
	if (!ft_absrelpath(cmd))
		ft_paths(scmd);
	if (!cmd->path && !(cmd->stat & EX_OK))
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
		if (!access(cmd->arr[0], X_OK))
		{
			if (dir)
				ft_helpabsrelpath(dir, cmd);
			else
			{
				cmd->stat |= EX_OK;
				cmd->path = ft_strdup(cmd->arr[0]);
			}
		}
		else
		{
			cmd->stat |= SLASH | CMD_KO;
			cmd->path = ft_strdup(cmd->arr[0]);
		}
		return (1);
	}
	return (0);
}
