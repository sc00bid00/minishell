/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:08:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/28 15:08:40 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

/* clean up t_list */
void	ft_cleanlst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

/* clean up t-list ** */
void	ft_cleanscmd(t_scmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->arr[i])
	{
		ft_cleanlst(cmd->arr[i]);
		i++;
	}
	free(cmd->arr);
	free(cmd);
}

/* clear t_token allocation */
void	ft_cleantkn(t_token *tkn)
{
	if (tkn->lst)
		ft_cleanlst(tkn->lst);
	if (tkn)
		free(tkn);
}

/* clean up and clear t_scmd and contained structs */
void	ft_cleancmd(t_scmd *scmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (scmd && scmd->cmd && scmd->cmd[i])
	{
		tmp = scmd->cmd[i];
		if (tmp->in_name)
			free(tmp->in_name);
		if (tmp->out_name)
			free(tmp->out_name);
		if (tmp->path)
			free(tmp->path);
		if (tmp->arr)
			ft_freesplit(tmp->arr);
		free(tmp);
		i++;
	}
	free(scmd->cmd);
}
