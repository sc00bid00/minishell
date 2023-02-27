/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prexec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:58:28 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:58 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	ft_isword(t_list *lst, int *count, t_scmd *scmd)
{
	t_cmd	*tmp;
	t_list	*tmp2;
	int		i;

	tmp = scmd->cmd[scmd->count];
	tmp->arr = ft_calloc(*count + 1, sizeof(char *));
	if (!tmp->arr)
		return (0);
	tmp2 = lst;
	i = 0;
	while (tmp2)
	{
		tmp->arr[i] = ft_strdup(tmp2->content);
		tmp2 = tmp2->next;
		i++;
	}
	return (1);
}

void	ft_isout(t_list *lst, int *count, t_scmd *scmd)
{
	int		rule;
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	if (!ft_strncmp(lst->content, ">>", 2))
		rule = O_WRONLY | O_CREAT | O_APPEND;
	else
		rule = O_WRONLY | O_CREAT | O_TRUNC;
	if (lst->next)
	{
		tmp->out_name = ft_strdup(lst->next->content);
		tmp->fd_out = open(tmp->out_name, rule, 0644);
	}
	*count -= 2;
}

void	ft_isheredoc(char *limiter, t_scmd *scmd)
{
	t_cmd	*tmp;
	char	*block;
	char	tmp_s[1];

	tmp_s[0] = 65 + scmd->count;
	tmp = scmd->cmd[scmd->count];
	tmp->in_name = ft_strjoin(".hdoc_", tmp_s);
	tmp->fd_in = open(tmp->in_name, O_RDWR | O_CREAT, 0644);
	while (1)
	{
		ft_printf("> ");
		block = get_next_line(0);
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
		tmp = scmd->cmd[scmd->count];
		if (!ft_strncmp(lst->content, "<<", 2))
		{
			tmp->hd_flag = 1;
			ft_isheredoc(lst->next->content, scmd);
		}
		else
		{
			if (!tmp->hd_flag)
			{
				tmp->in_name = ft_strdup(lst->next->content);
				tmp->fd_in = open(tmp->in_name, O_RDONLY, 0644);
			}
			else
			{
				/* manage open error if file invalid */
			}
		}
	}
	*count -= 2;
}
