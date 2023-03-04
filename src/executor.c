/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:27 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/04 12:12:37 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* wait children processes, feedback exitstatus */
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

/* infile to STDIN, if existing and accessible */
int	ft_firstcmd(t_scmd *scmd)
{
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	if (!tmp->in_name)
		dup2(scmd->fd[0], STDIN_FILENO);
	else
	{
		tmp->fd_in = open(tmp->in_name, O_RDONLY, 0644);
		if (tmp->fd_in < 0)
		{
			perror(tmp->in_name);
			return (0);
		}
		dup2(tmp->fd_in, STDIN_FILENO);
		close(tmp->fd_in);
	}
	return (1);
}

/* STDOUT to pipe, or to outfile if last cmd */
int	ft_pipein(t_scmd *scmd)
{
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	if (tmp->fd_out == 1 && (scmd->count == scmd->n_scmd - 1))
		dup2(tmp->fd_out, STDOUT_FILENO);
	else if (!tmp->out_name || access(tmp->out_name, F_OK))
		dup2(scmd->fd[1], STDOUT_FILENO);
	else
	{
		tmp->fd_out = open(tmp->out_name, tmp->rule, 0644);
		if (tmp->fd_out == -1)
		{
			perror(tmp->out_name);
			return (0);
		}
		dup2(tmp->fd_out, STDOUT_FILENO);
		if (tmp->fd_out > 1)
			close(tmp->fd_out);
	}
	return (1);
}

/* child processes execve*/
int	ft_child(t_scmd	*scmd)
{
	int		err;
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	if (!ft_helpexecutor(scmd))
		return (0);
	if (!tmp->path)
	{
		if (tmp->arr)
		{
			ft_putstr_fd("command not found : ", STDERR_FILENO);
			ft_putstr_fd(tmp->arr[0], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		return (0);
	}
	err = execve(tmp->path, tmp->arr, scmd->envp);
	if (err == -1)
	{
		if (tmp->arr)
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
		if (!ft_builtin(scmd))
		{
			if (!ft_helppipe(scmd))
				return (0);
			else
			{
				close(scmd->fd[1]);
				dup2(scmd->fd[0], STDIN_FILENO);
				close(scmd->fd[0]);
			}
		}
		scmd->count++;
	}
	ft_wait(scmd);
	return (scmd->flag);
}
