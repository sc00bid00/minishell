/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:39:58 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/03 14:44:10 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_spoillist_util(char *tmps, t_list **copy)
{
	ft_lstadd_back(copy, ft_lstnew(ft_strdup(tmps)));
	free(tmps);
	tmps = NULL;
}

void	ft_spoillist(t_token *tkn)
{
	t_list	*tmp;
	t_list	*copy;
	char	*tmps;

	copy = NULL;
	tmp = tkn->lst;
	while (tkn->lst)
	{
		if (tmp->content && (!ft_strncmp(tmp->content, "\'\'", 3)
				|| !ft_strncmp(tmp->content, "\"\"", 3)))
			tmps = NULL;
		else if (tmp->content && ((char *)tmp->content)[0] == '\"')
			tmps = ft_strtrim((char *)tmp->content, "\"");
		else if (tmp->content && ((char *)tmp->content)[0] == '\'')
			tmps = ft_strtrim((char *)tmp->content, "\'");
		else if (tkn->lst->content)
			tmps = ft_strdup((char *)tkn->lst->content);
		tmp = tkn->lst->next;
		free(tkn->lst->content);
		free(tkn->lst);
		if (tmps)
			ft_spoillist_util(tmps, &copy);
		tkn->lst = tmp;
	}
	tkn->lst = copy;
}
