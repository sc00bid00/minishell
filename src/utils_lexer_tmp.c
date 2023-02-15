/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_tmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:07:47 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 15:19:50 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/* print lst->content to stdout */
void	tmp_prtlst(t_token *tkn)
{
	t_list	*tmp;

	ft_printf("*****\ntemp output for debugginig purpose\n");
	ft_printf("*****\ninput string \"%s\"\n*****\n", tkn->str);
	tmp = tkn->lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_printf("*****\nchain with %d nodes\n*****\n", tkn->count);
}
