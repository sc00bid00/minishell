/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prexec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:58:28 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/26 12:59:12 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	ft_isword(t_list *lst, int count, t_scmd *scmd)
{
	t_cmd	*tmp;
	t_list	*tmp2;
	int		i;

	tmp->arr = ft_alloc(count + 1, sizeof(char *));
	if (!tmp->arr)
		return (0);
	i = 0;
	while (i < count)
	{
		tmp2 = lst;
		if (tmp2)
		{
			tmp->arr[scmd->count][i] = ft_strdup(tmp2->content);
			tmp2 = tmp2->next;
		}
		i++;
	}
	return (1);
}

void	ft_isout(t_list *lst, int *count, t_scmd *scmd)
{
	int		rule;
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	if (!ft_strncmp(lst->content, "<<", 2))
		rule = O_WRONLY | O_CREAT | O_APPEND;
	else
		rule = O_WRONLY | O_CREAT | O_TRUNC;
	if (lst->next)
	{
		tmp->in_name = ft_strdup(lst->next->content);
		tmp->fd_out = open(tmp->in_name, rule, 0644);
	}
	*count -= 2;
}

void	ft_isheredoc(char *limiter, t_scmd *scmd)
{
	t_cmd	*tmp;
	char	*block;

	tmp = scmd->cmd[scmd->count];
	tmp->in_name = ft_strjoin(".hdoc_", ft_atoi(scmd->count));
	tmp->fd_in = open(tmp->in_name, O_RDWR | O_CREAT, 0644);
	while (1)
	{
		block = get_next_line(tmp->fd_in);
		if (!ft_strncmp(block, limiter, ft_strlen(block) - 1) \
			&& ft_strlen(limiter) == ft_strlen(block) - 1)
		{
			free(block);
			break ;
		}
		else
			write(tmp->fd_in, block, ft_strlen(block));
		free(block);
	}
}

void	ft_isin(t_list *lst, int *count, t_scmd *scmd)
{
	t_cmd	*tmp;

	if (lst->next)
	{
		if (!ft_strncmp(lst->content, "<<", 2))
			ft_isheredoc(lst->next->content, scmd);
		else
		{
			tmp = scmd->cmd[scmd->count];
			tmp->in_name = ft_strdup(lst->next->content);
			tmp->fd_in = open(tmp->in_name, O_RDONLY, 0644);
		}
	}
	*count -= 2;
}
