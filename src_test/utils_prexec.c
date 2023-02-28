/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prexec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:58:28 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/28 10:42:48 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	ft_isword(t_list **lst, int *count, t_scmd *scmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = scmd->cmd[scmd->count];
	tmp->arr = ft_calloc(*count + 1, sizeof(char *));
	if (!tmp->arr)
		return (0);
	i = 0;
	while (*lst)
	{
		tmp->arr[i] = ft_strdup((*lst)->content);
		*lst = (*lst)->next;
		i++;
	}
	return (1);
}

void	ft_isout(t_list *lst, int *count, t_scmd *scmd)
{
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	if (!ft_strncmp(lst->content, ">>", 2))
		tmp->rule = O_WRONLY | O_CREAT | O_APPEND;
	else
		tmp->rule = O_WRONLY | O_CREAT | O_TRUNC;
	if (lst->next)
	{
		tmp->out_name = ft_strdup(lst->next->content);
		tmp->fd_out = open(tmp->out_name, tmp->rule, 0644);
		close(tmp->fd_out);
	}
	*count -= 2;
}

void	ft_isheredoc(char *limiter, t_scmd *scmd)
{
	t_cmd	*tmp;
	char	*block;
	char	tmp_s[2];

	tmp_s[0] = 65 + scmd->count;
	tmp_s[1] = '\0';
	tmp = scmd->cmd[scmd->count];
	tmp->in_name = ft_strjoin("/var/tmp/.hdoc_", tmp_s);
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
	close(tmp->fd_in);
}

static void	ft_invalid(char	*filename, t_scmd *scmd)
{
	t_cmd	*tmp;

	tmp = scmd->cmd[scmd->count];
	if (access(filename, R_OK | F_OK) < 0)
	{
		if (tmp->in_name)
			free(tmp->in_name);
		tmp->in_name = ft_strdup(filename);
		tmp->fd_in = -1;
		tmp->err_flag = 1;
	}
	else
	{
		if (tmp->in_name)
			free(tmp->in_name);
		tmp->in_name = ft_strdup(filename);
		tmp->fd_in = 3;
	}
}

void	ft_isin(t_list *lst, t_scmd *scmd)
{
	t_cmd	*tmp;

	if (lst->next)
	{
		tmp = scmd->cmd[scmd->count];
		if (!ft_strncmp(lst->content, "<<", 2))
		{
			tmp->hd_flag = 1;
			if (tmp->in_name)
				free(tmp->in_name);
			ft_isheredoc(lst->next->content, scmd);
		}
		else
		{
			if (!tmp->hd_flag || !tmp->err_flag)
				ft_invalid(lst->next->content, scmd);
		}
	}
}
