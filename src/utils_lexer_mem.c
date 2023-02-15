/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:08:58 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 15:09:26 by lsordo           ###   ########.fr       */
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

/* return 0ed t_token elements */
void	ft_init_tkn(t_token *tkn)
{
	tkn->lst = NULL;
	tkn->c_sta = 0b0000000;
	tkn->p_sta = 0b0000000;
	tkn->curr = 0;
	tkn->prev = 0;
	tkn->count = 0;
}
