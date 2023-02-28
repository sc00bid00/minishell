/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:58:03 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/28 16:20:25 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	ft_validpath(char *path)
{
	if (!access(path, X_OK))
		return (1);
	return (0);
}

void	ft_paths(t_scmd *scmd)
{
	int		j;
	char	**arr;
	char	*tmp;

	arr = ft_split(getenv("PATH"), ':');
	j = 0;
	while (arr && arr[j])
	{
		tmp = ft_strjoin(arr[j], "/");
		scmd->cmd[scmd->count]->path = \
			ft_strjoin(tmp, scmd->cmd[scmd->count]->arr[0]);
		free(tmp);
		if (ft_validpath(scmd->cmd[scmd->count]->path))
			break ;
		free(scmd->cmd[scmd->count]->path);
		scmd->cmd[scmd->count]->path = NULL;
		j++;
	}
	ft_freesplit(arr);
}

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
		ft_isword(tmp, count, scmd);
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
