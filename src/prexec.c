/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:58:03 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 13:10:47 by lsordo           ###   ########.fr       */
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
	if (arr)
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

int	ft_absrelpath(t_cmd *cmd)
{
	DIR	*dir;

	dir = NULL;
	cmd->path = NULL;
	if (cmd->arr && ft_strchr(cmd->arr[0], '/'))
	{
		dir = opendir(cmd->arr[0]);
		if (dir)
		{
			cmd->stat |= IS_DIR;
			closedir(dir);
		}
		if (!access(cmd->arr[0], X_OK) && ft_strncmp(cmd->arr[0], "./", 2) && ft_strncmp(cmd->arr[0], "../", 3))
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
		ft_putnbr_fd(cmd->stat, 2 );
		ft_putendl_fd("debug checkin", 2);
		return (1);
	}
	return (0);
}

int	ft_prexec(t_scmd *scmd)
{
	t_list	*tmp;
	t_cmd	*cmd;
	int		count;

	scmd->count = 0;
	while (scmd->arr && scmd->arr[scmd->count])
	{
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
		if (!ft_absrelpath(cmd))
			ft_paths(scmd);
		if (!cmd->path)
			cmd->stat |= CMD_KO;
		scmd->count++;
	}
	return (1);
}
