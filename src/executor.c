/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:54:30 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/11 15:23:34 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_wait(t_scmd *scmd)
{
	t_list	*tmp;

	while (1)
	{
		if (waitpid(-1, &scmd->wstatus, 0) == -1)
			break ;
		scmd->flag = WEXITSTATUS(scmd->wstatus);
	}
	tmp = scmd->hdocs;
	while (tmp)
	{
		unlink(tmp->content);
		tmp = tmp->next;
	}
}

void	ft_execute(t_scmd *scmd)
{
	t_cmd	*cmd;
	int		err;

	cmd = scmd->cmd[scmd->count];
	cmd->err_flag = 0;
	if (!cmd->path)
	{
		if (cmd->arr && cmd->arr[0])
		{
			ft_eerr(cmd, 127, "minishell : command not found : ", cmd->arr[0]);
			return ;
		}
		err = execve(cmd->path, cmd->arr, scmd->envp);
		{
			if (err == -1)
			{
				if (cmd->arr && cmd->arr[0])
				{
					ft_eerr(cmd, errno, "minishell : ", \
						strerror(cmd->err_flag));
					return ;
				}
			}
		}
	}
}

void	ft_dupfiles(t_scmd *scmd)
{
	t_cmd	*cmd;

	if (scmd->cmd[scmd->count])
		cmd = scmd->cmd[scmd->count];
	if (scmd->id == 0 && cmd->fd_in > 0)
	{
		cmd->fd_in = open(cmd->in_name, O_RDONLY, 0644);
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (scmd->id == 0 && scmd && scmd->cmd \
		&& scmd->cmd[scmd->count]->fd_out > 1)
	{
		cmd->fd_out = open(cmd->out_name, cmd->rule, 0644);
		dup2(scmd->cmd[scmd->count]->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (scmd->id != 0)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
	}
}

void	ft_duppipe(t_scmd *scmd)
{
	if (scmd->id == 0)
	{
		close(scmd->fd[0]);
		if (scmd->count < scmd->n_scmd - 1)
			dup2(scmd->fd[1], STDOUT_FILENO);
		close(scmd->fd[1]);
	}
	else
	{
		close(scmd->fd[1]);
		if (scmd->count < scmd->n_scmd - 1)
			dup2(scmd->fd[0], STDIN_FILENO);
		close(scmd->fd[0]);
	}
}

void	ft_exec(t_scmd *scmd)
{
	scmd->count = 0;
	while (scmd && scmd->cmd && scmd->cmd[scmd->count])
	{
		if (pipe(scmd->fd) == -1)
			exit(EXIT_FAILURE);
		scmd->id = fork();
		if (scmd->id == -1)
			exit(EXIT_FAILURE);
		ft_duppipe(scmd);
		ft_dupfiles(scmd);
		ft_execute(scmd);
		ft_wait(scmd);
		scmd->count++;
	}
	return ;
}
