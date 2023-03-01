/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:27 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/01 16:56:47 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>
#include <executor.h>

/* wait children processes, feedback exitstatus */
void	ft_wait(t_scmd *scmd)
{
	while (1)
	{
		if (waitpid(-1, &scmd->wstatus, 0) == -1)
			break ;
		scmd->flag = WEXITSTATUS(scmd->wstatus);
	}
}

/* infile to STDIN, if existing and accessible */
int	ft_firstcmd(t_scmd *scmd)
{
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	tmp->fd_in = open(tmp->in_name, O_RDONLY, 0644);
	if (tmp->fd_in < 0)
	{
		perror(tmp->in_name);
		return (0);
	}
	dup2(tmp->fd_in, STDIN_FILENO);
	close(tmp->fd_in);
	return (1);
}

/* STDOUT to pipe, or to outfile if last cmd */
int	ft_pipein(t_scmd *scmd)
{
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	tmp->fd_out = open(tmp->out_name, tmp->rule, 0644);
	if (tmp->fd_out == -1)
	{
		perror(tmp->out_name);
		return (0);
	}
	dup2(tmp->fd_out, STDOUT_FILENO);
	close(tmp->fd_out);
	return (1);
}

/* child processes execve*/
int	ft_child(t_scmd	*scmd)
{
	int		err;
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	close(scmd->fd[0]);
	if (!ft_pipein(scmd))
		return (0);
	if (!ft_firstcmd(scmd))
		return (0);
	if (!tmp->path)
	{
		ft_putstr_fd("command not found : ", STDERR_FILENO);
		ft_putstr_fd(tmp->arr[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
	}
	err = execve(tmp->path, tmp->arr, scmd->envp);
	if (err == -1)
	{
		perror(tmp->arr[0]);
		return (0);
	}
	return (1);
}

/* pipe, fork, STDIN to pipe (parent process)*/
int	ft_pipe(t_scmd *scmd)
{
	scmd->count = 0;
	while (scmd && scmd->cmd && scmd->cmd[scmd->count])
	{
		if (pipe(scmd->fd) == -1)
			return (0);
		scmd->id = fork();
		if (scmd->id == -1)
			return (0);
		if (scmd->id == 0)
		{
			if (!ft_child(scmd))
				return (0);
		}
		else
		{
			close(scmd->fd[1]);
			dup2(scmd->fd[0], STDIN_FILENO);
			close(scmd->fd[0]);
		}
		scmd->count++;
	}
	ft_wait(scmd);
	return (scmd->flag);
}
