/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:58:03 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/03 13:40:22 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell.h>

/* return 1 if env path and command combination is X_OK, 0 else*/
int	ft_validpath(char *path)
{
	if (!access(path, X_OK))
		return (1);
	return (0);
}

/* return t_scmd->cmd[i]->path if combination ok, NULL else */
void	ft_paths(t_scmd *scmd)
{
	int		j;
	char	**arr;
	char	*tmp;
	t_cmd	*cmd;

	arr = ft_split(getenv("PATH"), ':');
	j = 0;
	while (arr && arr[j])
	{
		cmd = scmd->cmd[scmd->count];
		if (!cmd->arr || !cmd->arr[0])
			cmd->path = NULL;
		else
		{
			tmp = ft_strjoin(arr[j], "/");
			cmd->path = ft_strjoin(tmp, cmd->arr[0]);
			free(tmp);
			if (ft_validpath(cmd->path))
				break ;
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
	else if (tmp && *tmp)
	{
		if (!ft_isword(tmp, count, scmd))
			return (0);
	}
	return (1);
}

int	ft_prexec(t_scmd *scmd)
{
	t_list	*tmp;
	int		count;

	scmd->count = 0;
	while (scmd->arr && scmd->arr[scmd->count])
	{
		tmp = scmd->arr[scmd->count];
		count = ft_lstsize(tmp);
		if (!ft_init_cmd(scmd))
			return (0);
		while (tmp)
		{
			if (!ft_direct(&tmp, &count, scmd))
				return (0);
			if (tmp)
				tmp = tmp->next;
		}
		ft_paths(scmd);
		scmd->count++;
	}
	return (1);
}