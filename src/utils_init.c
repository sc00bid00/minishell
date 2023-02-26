/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:39:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/26 08:13:15 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

/* return int num of simple cmds out of t_token.str */
int	ft_ctscmd(t_token *tkn)
{
	t_list	*tmp;
	int		i;

	tmp = tkn->lst;
	i = 0;
	while (tmp)
	{
		if (((char *)(tmp->content))[0] == '|')
			i++;
		tmp = tmp->next;
	}
	i++;
	return (i);
}

/* return allocated and 0 initilized t_token */
t_token	*ft_init_tkn(char *str)
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
	return (tkn);
}

/* return 0 initialized and allocated t_scmd * */
t_scmd	*ft_init_scmd(t_token *tkn)
{
	t_scmd	*scmd;

	scmd = malloc(sizeof(t_scmd));
	if (!scmd)
		return (NULL);
	scmd->n_scmd = ft_ctscmd(tkn);
	scmd->arr = ft_calloc(scmd->n_scmd + 1, sizeof(t_list *));
	if (!scmd->arr)
	{
		ft_cleantkn(tkn);
		return (NULL);
	}
	scmd->count = 0;
	scmd->arr[scmd->n_scmd] = NULL;
	return (scmd);
}
