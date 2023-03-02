/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/02 17:54:59 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>
#include <executor.h>

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*tkn;
	t_scmd	*scmd;
	int		ret;

	if (!argc && !argv)
		return (1);
	// BASTARDS LIST:
	// heredoc not redirecting *** solved ***
	// str = "< testfile | < testfile cat -e >> out << stop";
	// persisting hdoc *** solved ***
	// str = "< testfile | <testfile cat -e >> out << stop";
	// token not recognized
	// str = "< Makefile wc -l > << stop out2";
	// bad address *** solved ***
	// str = "< Makefile cat -e | wc -l >> out3 > out4";
	ft_printf("%s\n", str);
	tkn = ft_lex(str);
	scmd = ft_parse(tkn, envp);
	ret = ft_pipe(scmd);
	ft_cleancmd(scmd);
	ft_cleanscmd(scmd);
	ft_cleantkn(tkn);
	return (ret);
	// return (1);
}
