/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:08:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 17:27:24 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/* clear t_token allocation */
void	ft_cleanup(t_token *tkn)
{
	t_list	*tmp;

	if (tkn->lst)
	{
		while (tkn->lst)
		{
			tmp = tkn->lst->next;
			free(tkn->lst->content);
			free(tkn->lst);
			tkn->lst = tmp;
		}
	}
	if (tkn)
		free(tkn);
}

/* return allocated and 0 initilized t_token*/
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
