/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:54:48 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/22 10:56:10 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_redirect(t_scmd *scmd)
{
	t_cmd	*cmd;

	cmd = scmd->cmd[scmd->count];
	if (!cmd->arr)
	{
		if (cmd->stat & OUT_OK)
			exit(0);
		if (cmd->stat & IN_OK)
			exit(1);
	}
	if (cmd->stat & IN_OK && cmd->stat & EX_OK)
	{
		cmd->fd_in = open(cmd->in_name, O_RDONLY, 0644);
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		close(scmd->fd[0]);
	}
	if (cmd->stat & OUT_OK && cmd->stat & EX_OK)
	{
		cmd->fd_out = open(cmd->out_name, cmd->rule, 0644);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		close(scmd->fd[1]);
	}
}

void	ft_cmdissues(t_scmd *scmd)
{
	t_cmd	*cmd;

	cmd = scmd->cmd[scmd->count];
	if (cmd->stat & CMD_KO)
	{
		ft_eerr("minishell: ", cmd->arr[0], ": command not found");
		cmd->err_flag = 127;
	}
	else if (cmd->stat & 0)
		cmd->err_flag = 0;
	if (cmd->stat & IN_OK)
		close(cmd->fd_in);
	if (cmd->stat & OUT_OK)
		close(cmd->fd_out);
	close(scmd->fd[0]);
	close(scmd->fd[1]);
	exit(cmd->err_flag);
}

void	ft_fileissues(t_scmd *scmd)
{
	t_cmd	*cmd;

	cmd = scmd->cmd[scmd->count];
	if (cmd->stat & IN_KO)
	{
		ft_eerr("minishell: ", cmd->in_name, \
			": No such file or directory");
		cmd->err_flag = 1;
	}
	else if (cmd->stat & OUT_KO)
	{
		ft_eerr("minishell: ", cmd->out_name, ": Permission denied");
		cmd->err_flag = 1;
	}
	close(scmd->fd[0]);
	close(scmd->fd[1]);
	exit(cmd->err_flag);
}

void	ft_execute(t_scmd *scmd)
{
	t_cmd	*cmd;
	int		err;

	cmd = scmd->cmd[scmd->count];
	err = execve(cmd->path, cmd->arr, scmd->envp);
	if (err == -1)
	{
		ft_eerr("minishell: ", strerror(errno), NULL);
		exit(1);
	}
}

void	ft_noredirect(t_scmd *scmd)
{
	t_cmd	*cmd;

	cmd = scmd->cmd[scmd->count];
	close(scmd->fd[0]);
	if (!(cmd->stat & 0b001100) && scmd->count < scmd->n_scmd - 1)
		dup2(scmd->fd[1], STDOUT_FILENO);
	close(scmd->fd[1]);
}
