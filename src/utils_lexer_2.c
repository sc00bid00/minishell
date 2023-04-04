/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:04:40 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 19:06:49 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helplsttostr(t_list *tmplst, int *i)
{
	while (tmplst)
	{
		if (tmplst->content)
			*i += ft_strlen((char *)tmplst->content);
		tmplst = tmplst->next;
	}
}

void	ft_helpexpdollar(char **tmp, t_list *lst, t_token *tkn)
{
	t_list	*tmplst;
	t_list	*tmplst2;

	tmplst = ft_strtolst((char *)lst->content);
	tmplst2 = ft_moddollar(tmplst, tkn);
	*tmp = ft_lsttostr(tmplst2);
	ft_cleanlst(tmplst);
}
