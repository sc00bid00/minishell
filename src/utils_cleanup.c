/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:08:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/20 17:04:04 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* clean up t_list */
void	ft_cleanlst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		if (lst->content)
			free(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	free(lst);
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
	if (cmd->hdocs)
		ft_cleanlst(cmd->hdocs);
	if (cmd->envp)
		ft_freesplit(cmd->envp);
	free(cmd);
}

/* clear t_token allocation */
void	ft_cleantkn(t_token *tkn)
{
	if (tkn && tkn->lst)
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

void	ft_clean_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env && env->next)
	{
		if (env->var_name)
			free(env->var_name);
		if (env->var_content)
			free (env->var_content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}