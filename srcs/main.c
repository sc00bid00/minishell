/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/01 10:25:53 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*tkn;
	t_scmd	*scmd;

	str = "cat -e > out1    \
		| grep <Makefile << stop <invalid $USER 2 > out2 >>out \
		| wc -l < Makefile";
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
