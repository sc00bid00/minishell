/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/27 18:46:46 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	main(void)
{
	char	*str;
	t_token	*tkn;
	t_scmd	*scmd;

	str = "cat -e < invalid1 < invalid2 << stop << stop \
		| grep $USER >>out <<stop";
	tkn = ft_lex(str);
	scmd = ft_parse(tkn);
	ft_printf("counted %d simple command(s)\n", scmd->n_scmd);
	ft_printf("input\n%s\n", tkn->str);
	tmp_prtarrlst(scmd);
	tmp_prtcmd(scmd);
	ft_cleanscmd(scmd);
	ft_cleantkn(tkn);
	return (0);
}
