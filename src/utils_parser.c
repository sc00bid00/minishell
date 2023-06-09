/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:20:38 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/31 17:28:58 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* return words out of t_token.lst to t_scmd.t_list ** */
void	ft_getwords(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;

	arr = cmd->arr;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] == '|')
		{
			free(tmp->content);
			tmp->content = NULL;
			break ;
		}
		if (tmp->content)
		{
			ft_lstadd_back(&(arr[cmd->count]), \
				ft_lstnew(ft_strdup(tmp->content)));
			free(tmp->content);
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

/* return > and filename out of t_token.lst to t_scmd.t_list ** */
void	ft_getred(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;
	int		flag;

	arr = cmd->arr;
	tmp = tkn->lst;
	flag = 0;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strncmp(tmp->content, ">", 1)
				|| !ft_strncmp(tmp->content, ">>", 1)
				|| !ft_strncmp(tmp->content, "<", 1) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], \
				ft_lstnew(ft_strdup(tmp->content)));
			free(tmp->content);
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

/* return << limiter out of t_token.lst to t_scmd.t_list ** */
void	ft_gethdoc(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;
	int		flag;

	arr = cmd->arr;
	tmp = tkn->lst;
	flag = 0;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strncmp(tmp->content, "<<", 2) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], \
				ft_lstnew(ft_strdup(tmp->content)));
			free(tmp->content);
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}
