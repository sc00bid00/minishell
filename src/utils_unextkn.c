/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unexptkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:52:00 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/06 18:52:45 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpunextkn(t_token *tkn, t_list *tmp)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(tmp->content, 2);
	write (2, "\'\n", 2);
	ft_cleantkn(tkn);
}

/* return NULL if unexpected token found */
t_token	*ft_unextkn(t_token *tkn)
{
	t_list	*tmp;
	int		token;

	token = 0b0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && (!ft_strncmp(tmp->content, ">", 1) \
		|| !ft_strncmp(tmp->content, "<", 1)))
		{
			if (token & 1)
			{
				ft_helpunextkn(tkn, tmp);
				return (NULL);
			}
			else
				token |= 1;
		}
		else
			token &= 0;
		tmp = tmp->next;
	}
	return (tkn);
}
