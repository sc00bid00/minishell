/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prexec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:58:28 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 16:37:27 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isword(t_list **lst, int *count, t_scmd *scmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = scmd->cmd[scmd->count];
	tmp->arr = ft_calloc(*count + 1, sizeof(char *));
	if (!tmp->arr)
		return (0);
	i = 0;
	while (*lst && (*lst)->content)
	{
		tmp->arr[i] = ft_strdup((*lst)->content);
		i++;
		*lst = (*lst)->next;
	}
	tmp->argc = i;
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
		if (tmp->out_name)
			free(tmp->out_name);
		tmp->out_name = ft_strdup(lst->next->content);
		tmp->fd_out = open(tmp->out_name, tmp->rule, 0644);
		if (tmp->fd_out == -1 && !(tmp->stat & 0b000101))
		{
			if (tmp->stat & 0b000010)
				tmp->stat ^= 0b000010;
			tmp->stat |= 0b000100;
		}
		else if (!(tmp->stat & 0b000101))
			tmp->stat |= 0b001000;
		if (tmp->fd_out != -1)
			close(tmp->fd_out);
	}
	*count -= 2;
}

char	*ft_dollarsubst2(char *str, t_scmd *scmd)
{
	t_env	*env_var;
	char	*tmp;

	tmp = NULL;
	if (str && str[0] == '0')
	{
		env_var = ret_var(&scmd->env, "SHELL");
		if (env_var)
			tmp = ft_strjoin(env_var->var_content, &str[1]);
	}
	else if (str && ft_isdigit(str[0]))
		tmp = ft_strdup(&str[1]);
	else if (str)
	{
		env_var = ret_var(&scmd->env, str);
		if (env_var)
			tmp = ft_strdup(env_var->var_content);
	}
	return (tmp);
}

void	ft_hdocdollar(char **str, t_scmd *scmd)
{
	t_list	*lst;
	t_list	*tmp;
	char	*s;

	lst = NULL;
	lst = ft_strtolstecho(*str);
	tmp = lst;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] == '$' && ((char *)tmp->content)[1])
		{
			s = ft_strdup(&((char *)tmp->content)[1]);
			free(tmp->content);
			tmp->content = ft_dollarsubst2(s, scmd);
			free(s);
		}
		tmp = tmp->next;
	}
	free(*str);
	*str = ft_lsttostr(lst);
	ft_cleanlst(lst);
}

void	ft_isheredoc(char *limiter, t_scmd *scmd)
{
	t_cmd	*tmp;
	char	*block;

	tmp = scmd->cmd[scmd->count];
	ft_helpisheredoc(scmd, &tmp);
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
		else if (block && ft_strchr(block, '$'))
		{
			ft_hdocdollar(&block, scmd);
			write(tmp->fd_in, block, ft_strlen(block));
		}
		else
			write(tmp->fd_in, block, ft_strlen(block));
		free(block);
	}
	close(tmp->fd_in);
	if (!(tmp->stat & 0b000101))
		tmp->stat |= 0b000010;
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
		if (tmp->stat & 0b000010)
			tmp->stat ^= 0b000010;
		tmp->stat |= 0b000001;
	}
	else
	{
		if (tmp->in_name)
			free(tmp->in_name);
		tmp->in_name = ft_strdup(filename);
		tmp->fd_in = 3;
		tmp->stat |= 0b000010;
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
			if (!access(tmp->in_name, F_OK))
				ft_lstadd_back(&scmd->hdocs, \
				ft_lstnew(ft_strdup(tmp->in_name)));
		}
		else
		{
			if (!(tmp->stat & 0b000101) && !tmp->hd_flag)
				ft_invalid(lst->next->content, scmd);
		}
	}
}
