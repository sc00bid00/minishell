/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 17:26:59 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/* pass a string to ft_lex print out stuff and cleanup */
int	main(void)
{
	char	*str;
	t_token	*tkn;

	str = "< infile.txt cat -e| grep $USER >>out<< stop1 << stop2";
	tkn = ft_lex(str);
	tmp_prtlst(tkn);
	ft_cleanup(tkn);
	return (0);
}
