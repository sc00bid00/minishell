/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:58:03 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/03 05:53:02 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* return 1 if env path and command combination is X_OK, 0 else*/
int	ft_validpath(char *path)
{
	if (!access(path, X_OK))
		return (1);
	return (0);
}

char	**ft_arrpaths(t_scmd *scmd)
{
	t_env	*env_var;
	char	**arr;

	env_var = ret_var(&scmd->env, "PATH");
	if (env_var && env_var->var_content)
	{
		arr = ft_split(env_var->var_content, ':');
		return (arr);
	}
	return (NULL);
}

/* return t_scmd->cmd[i]->path if combination ok, NULL else */
void	ft_paths(t_scmd *scmd)
{
	int		j;
	char	**arr;
	t_cmd	*cmd;

	arr = ft_arrpaths(scmd);
	j = 0;
	while (arr && arr[j])
	{
		cmd = scmd->cmd[scmd->count];
		if (!cmd->arr || !cmd->arr[0])
			cmd->path = NULL;
		else
		{
			ft_helppaths(cmd, arr, j);
			if (ft_validpath(cmd->path))
			{
				cmd->stat |= 0b100000;
				break ;
			}
			free(cmd->path);
			cmd->path = NULL;
		}
		j++;
	}
	ft_freesplit(arr);
}

/* triage between in out or command, return NULL*/
int	ft_direct(t_list **tmp, int *count, t_scmd *scmd)
{
	if (tmp && *tmp && ((char *)(*tmp)->content)[0] == '<')
	{
		ft_isin(*tmp, scmd);
		*count -= 2;
		*tmp = (*tmp)->next;
	}
	else if (tmp && *tmp && ((char *)(*tmp)->content)[0] == '>')
	{
		ft_isout(*tmp, count, scmd);
		*tmp = (*tmp)->next;
	}
	else if (tmp && *tmp
		&& !(scmd->cmd[scmd->count]->stat & 0b000101))
	{
		if (!ft_isword(tmp, count, scmd))
			return (0);
	}
	return (1);
}

int	ft_prexec(t_scmd *scmd)
{
	t_list	*tmp;
	t_cmd	*cmd;
	int		count;
	DIR		*dir;

	scmd->count = 0;
	while (scmd->arr && scmd->arr[scmd->count])
	{
		dir = NULL;
		tmp = scmd->arr[scmd->count];
		count = ft_lstsize(tmp);
		if (!ft_init_cmd(scmd))
			return (0);
		cmd = scmd->cmd[scmd->count];
		while (tmp)
		{
			if (!ft_direct(&tmp, &count, scmd))
				return (0);
			if (tmp)
				tmp = tmp->next;
		}
		ft_paths(scmd);
		if (cmd->arr && cmd->arr[0] && cmd->arr[0][0] == '/')
			cmd->stat |= 0b010000;
		if (!cmd->path && cmd->arr && cmd->arr[0])
			cmd->stat |= 0b010000;
		if (cmd->arr)
			dir = opendir(cmd->arr[0]);
		if (!dir)
		{
			scmd->dir = 1;
			ft_error(SHELL, cmd->arr[0], NULL, ERROR_1);
			return (1);
		}
		if ((!(cmd->path) && cmd->arr && cmd->arr[0] && dir) ||
			(cmd->arr && cmd->arr[0] && cmd->arr[0][0] == '/'))
		{
			cmd->stat |= 0b1000000;
		}
		if (dir)
			closedir(dir);
		scmd->count++;
	}
	return (1);
}
