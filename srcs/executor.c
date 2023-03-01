/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:27 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/01 10:25:10 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>
#include <executor.h>

/* wait children processes, feedback exitstatus */
void	ft_wait(t_data *d)
{
	while (1)
	{
		if (waitpid(-1, &d->wstatus, 0) == -1)
			break ;
		d->flag = WEXITSTATUS(d->wstatus);
	}
}

/* infile to STDIN, if existing and accessible */
void	ft_firstcmd(t_data *d)
{
	if (d->ci == 0)
	{
		d->infiled = open(d->files[0], O_RDONLY, 0644);
		if (d->infiled < 0)
		{
			perror(d->files[0]);
			d->flag = errno;
			ft_cleanup(d);
		}
		dup2(d->infiled, STDIN_FILENO);
		close(d->infiled);
	}
}

/* STDOUT to pipe, or to outfile if last cmd */
void	ft_pipein(t_data *d)
{
	int	r;

	if (d->ci != d->cnum - 1)
		dup2(d->fd[1], STDOUT_FILENO);
	else
	{
		if (d->hd_offset)
			r = O_WRONLY | O_CREAT | O_APPEND;
		else
			r = O_WRONLY | O_CREAT | O_TRUNC;
		d->outfiled = open(d->files[1], r, 0644);
		if (d->outfiled == -1)
		{
			perror(d->files[1]);
			d->flag = errno;
			ft_cleanup(d);
		}
		dup2(d->outfiled, STDOUT_FILENO);
		close(d->outfiled);
	}
}

/* child processes execve*/
int	ft_child(t_scmd	*scmd)
{
	int		err;
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	close(scmd->fd[0]);
	ft_pipein(scmd);
	ft_firstcmd(scmd);
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
		perror(d->args[d->ci][0]);
		d->flag = errno;
		ft_cleanup(d);
	}
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
	return (1);
}
