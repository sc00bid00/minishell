/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/28 17:16:49 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	main(void)
{
	char	*str;
	t_token	*tkn;
	t_scmd	*scmd;

	str = "cat -e < Makefile > out1    \
		| grep <Makefile << stop <invalid $USER 2 > out2 >>out \
		| wc -l < invalid 2";
	tkn = ft_lex(str);
	scmd = ft_parse(tkn);
	ft_printf("counted %d simple command(s)\n\n", scmd->n_scmd);
	ft_printf("input\n%s\n\n", tkn->str);
	tmp_prtcmd(scmd);
	ft_cleancmd(scmd);
	ft_cleanscmd(scmd);
	ft_cleantkn(tkn);
	return (0);
}
