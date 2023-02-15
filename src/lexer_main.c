/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 16:26:47 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/* call ft_lex passing an allocated and initialized t_token
clean-up after use */
int	main(void)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (1);
	ft_init_tkn(tkn);
	tkn->str \
		= "< infile.txt cat -e| grep $USER >>out<< stop1 << stop2";
	ft_lex(tkn);
	tmp_prtlst(tkn);
	ft_cleanup(tkn);
	return (0);
}
