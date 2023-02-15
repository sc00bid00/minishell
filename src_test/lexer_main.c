/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 15:15:18 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/* main for test purpose*/
int	main(void)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (1);
	ft_init_tkn(tkn);
	tkn->str \
		= "\"$USER\" <   inf    cat '$USER'| wc -l << $USER $PATH \"PATH\" << end  |ls -la   \
		| echo   \"so la la\" >>out";
	ft_lex(tkn);
	tmp_prtlst(tkn);
	ft_cleanup(tkn);
	return (0);
}
