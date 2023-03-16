/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:39:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/16 08:39:29 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* return int num of simple cmds out of t_token.str */
int	ft_ctscmd(t_token *tkn)
{
	t_list	*tmp;
	int		i;

	tmp = tkn->lst;
	i = 0;
	while (tmp)
	{
		if (tmp->content && ((char *)(tmp->content))[0] == '|')
			i++;
		tmp = tmp->next;
	}
	i++;
	return (i);
}

/* return allocated and 0 initilized t_token */
t_token	*ft_init_tkn(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->str = str;
	tkn->lst = NULL;
	tkn->c_sta = 0b0000000;
	tkn->p_sta = 0b0000000;
	tkn->curr = 0;
	tkn->prev = 0;
	tkn->count = 0;
	tkn->env = env;
	return (tkn);
}

/* return 0 initialized and allocated t_scmd * */
t_scmd	*ft_init_scmd(t_token *tkn, char **arr, t_env *env)
{
	t_scmd	*scmd;

	(void)arr;
	scmd = malloc(sizeof(t_scmd));
	if (!scmd)
		return (NULL);
	scmd->n_scmd = ft_ctscmd(tkn);
	scmd->arr = ft_calloc(scmd->n_scmd + 1, sizeof(t_list *));
	scmd->cmd = ft_calloc(scmd->n_scmd + 1, sizeof(t_cmd *));
	scmd->hdocs = NULL;
	if (!(scmd->arr && scmd->cmd))
	{
		ft_cleantkn(tkn);
		free(scmd);
		return (NULL);
	}
	scmd->count = 0;
	scmd->arr[scmd->n_scmd] = NULL;
	scmd->envp = ft_arrenv(env);
	scmd->wstatus = 0;
	scmd->flag = 0;
	scmd->env = env;
	return (scmd);
}

/* return 0 initialized and allocated t_scmd->t_cmd * */
int	ft_init_cmd(t_scmd *scmd)
{
	t_cmd	*tmp;

	scmd->cmd[scmd->count] = malloc(sizeof(t_cmd));
	if (!scmd->cmd[scmd->count])
		return (0);
	tmp = scmd->cmd[scmd->count];
	tmp->arr = NULL;
	tmp->in_name = NULL;
	tmp->out_name = NULL;
	tmp->fd_in = 0;
	tmp->fd_out = 1;
	tmp->path = NULL;
	tmp->hd_flag = 0;
	tmp->err_flag = 0;
	tmp->rule = 0;
	tmp->stat = 0b000000;
	return (1);
}
