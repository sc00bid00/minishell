/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:54:30 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/02 15:36:22 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_wait(t_scmd *scmd)
{
	t_list	*tmp;
	int		ret;

	scmd->count = 0;
	while (scmd->n_scmd && scmd->count < scmd->n_scmd)
	{
		ret = waitpid(-1, &scmd->wstatus, 0);
		if (ret == scmd->id)
			g_exitstatus = WEXITSTATUS(scmd->wstatus);
		if (WIFSIGNALED(scmd->wstatus) && scmd->wstatus != 13)
			g_exitstatus = 128 + WTERMSIG(scmd->wstatus);
		scmd->count++;
	}
	tmp = scmd->hdocs;
	while (tmp)
	{
		unlink(tmp->content);
		tmp = tmp->next;
	}
}

void	ft_fdreset(t_scmd *scmd)
{
	dup2(scmd->store[0], STDIN_FILENO);
	dup2(scmd->store[1], STDOUT_FILENO);
	close(scmd->store[0]);
	close(scmd->store[1]);
}

void	ft_parent(t_scmd *scmd)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	close(scmd->fd[1]);
	if (scmd->count != 0 || scmd->count < scmd->n_scmd - 1)
		dup2(scmd->fd[0], STDIN_FILENO);
	close(scmd->fd[0]);
}

void	ft_child(t_scmd *scmd)
{
	t_cmd	*cmd;
	int		(*fun)(t_cmd *, t_env **);

	fun = ft_builtin(scmd);
	cmd = scmd->cmd[scmd->count];
	if (cmd->stat & FILE_KO)
		ft_fileissues(scmd);
	if (!cmd->builtin && cmd->stat & CMD_KO)
		ft_cmdissues(scmd);
	if (cmd->stat & RED_OK)
		ft_redirect(scmd);
	ft_noredirect(scmd);
	if (cmd->builtin)
	{
		fun(cmd, &scmd->env);
		exit (EXIT_SUCCESS);
	}
	else if (cmd->stat & EX_OK)
		ft_execute(scmd);
}

void	ft_exec(t_scmd *scmd)
{
	int	(*fun)(t_cmd *, t_env **);

	scmd->store[0] = dup(STDIN_FILENO);
	scmd->store[1] = dup(STDOUT_FILENO);
	scmd->count = 0;
	fun = ft_builtin(scmd);
	if (scmd->n_scmd == 1 && scmd->cmd[scmd->count] && scmd->cmd[scmd->count]->builtin)
	{
		scmd->id = 1;
		fun(*scmd->cmd, &scmd->env);
	}
	else
	{
		while (scmd && scmd->cmd && scmd->cmd[scmd->count])
		{
			if (pipe(scmd->fd) == -1)
				exit(EXIT_FAILURE);
			scmd->id = fork();
			if (scmd->id == -1)
				exit(EXIT_FAILURE);
			if (scmd->id == 0)
				ft_child(scmd);
			else
				ft_parent(scmd);
			scmd->count++;
		}
	}
	if (scmd->id != 0)
	{
		ft_wait(scmd);
		ft_fdreset(scmd);
	}
	return ;
}
