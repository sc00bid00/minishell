/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:17:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/10 14:43:59 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_helpexecutor(t_scmd *scmd)
{
	close(scmd->fd[0]);
	if (!ft_pipein(scmd))
		return (0);
	if (!ft_firstcmd(scmd))
		return (0);
	return (1);
}

/* return 1 if cmd->arr[0] is a builtin */
int	ft_builtin(t_scmd *scmd)
{
	int		(*builtin)(t_cmd *cmd, t_env *env);
	t_cmd	*tmp;

	(void)(builtin);
	tmp = scmd->cmd[scmd->count];
	if (tmp && tmp->arr && !ft_strncmp(tmp->arr[0], "cd", 2))
		builtin = &builtin_cd;
	else if (tmp && tmp->arr && !ft_strncmp(tmp->arr[0], "echo", 4))
		builtin = &builtin_echo;
	else if (tmp && tmp->arr && !ft_strncmp(tmp->arr[0], "exit", 4))
		builtin = &builtin_exit;
	else if (tmp && tmp->arr && !ft_strncmp(tmp->arr[0], "export", 6))
		builtin = &builtin_export;
	else if (tmp && tmp->arr && !ft_strncmp(tmp->arr[0], "env", 3))
		builtin = &builtin_env;
	else if (tmp && tmp->arr && !ft_strncmp(tmp->arr[0], "pwd", 3))
		builtin = &builtin_pwd;
	else if (tmp && tmp->arr && !ft_strncmp(tmp->arr[0], "unset", 5))
		builtin = &builtin_unset;
	else
		return (0);
	builtin(tmp, scmd->env);
	return (1);
}

int	ft_helppipe(t_scmd *scmd)
{
	scmd->id = fork();
	if (scmd->id == -1)
		return (0);
	if (scmd->id == 0)
	{
		if (!ft_child(scmd))
			return (0);
	}
	return (1);
}
