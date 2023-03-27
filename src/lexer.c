/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/27 08:36:06 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* return t_list nodes containing tokne char * */
void	ft_save(t_token *tkn)
{
	ft_lstadd_back(&(tkn->lst), \
		ft_lstnew(ft_substr(tkn->str, tkn->prev, tkn->curr - tkn->prev)));
	tkn->prev = tkn->curr;
	tkn->count++;
}

// /* return bitwise flags to split tokens */
// void	ft_getstatus(t_token *tkn)
// {
// 	if (tkn->str[tkn->curr] == '\'')
// 		tkn->c_sta = tkn->c_sta ^ 0b0000001;
// 	else if (tkn->str[tkn->curr] == '\"')
// 		tkn->c_sta = tkn->c_sta ^ 0b0000010;
// 	else
// 	{
// 		tkn->c_sta = tkn->c_sta & 0b0000011;
// 		if (tkn->str[tkn->curr] == '|')
// 			tkn->c_sta = tkn->c_sta | 0b0000100;
// 		else if (tkn->str[tkn->curr] == '>')
// 			tkn->c_sta = tkn->c_sta | 0b0001000;
// 		else if (tkn->str[tkn->curr] == '<')
// 			tkn->c_sta = tkn->c_sta | 0b0010000;
// 		else if (tkn->str[tkn->curr] == ' ')
// 			tkn->c_sta = tkn->c_sta | 0b0100000;
// 		else if (tkn->str[tkn->curr] > 32)
// 			tkn->c_sta = tkn->c_sta | 0b1000000;
// 	}
// }

// /* return t_token with t_list of tokens
// token is either a word or a metacharacter
// text in quotes is word */
// t_token	*ft_lex(char *str, t_env *env)
// {
// 	t_token	*tkn;

// 	tkn = ft_init_tkn(str, env);
// 	while (tkn->str && tkn->str[tkn->curr])
// 	{
// 		ft_getstatus(tkn);
// 		if (tkn->curr == 0)
// 			tkn->p_sta = tkn->c_sta;
// 		if (tkn->c_sta & 0b0000011)
// 			;
// 		else if (!(tkn->c_sta & 0b0000011) && !(tkn->p_sta & 0b0000001))
// 		{
// 			if ((tkn->c_sta >> 2) != (tkn->p_sta >> 2) && tkn->p_sta != 0)
// 				ft_save(tkn);
// 			if (tkn->c_sta == 0)
// 				tkn->prev = tkn->curr + 1;
// 		}
// 		tkn->p_sta = tkn->c_sta;
// 		tkn->curr++;
// 	}
// 	ft_helplexer(tkn);
// 	if (!ft_redsyntax(tkn))
// 		return (NULL);
// 	return (tkn);
// }

int	ft_flag(char c)
{
	int		flag;

	flag = 0;
	if (c == '\'')
		flag |= SINGLE_Q;
	else if (c == '"')
		flag |= DOUBLE_Q;
	else if (c == ' ')
		flag |= SPCE;
	else if (c == '<')
		flag |= RIN;
	else if (c == '>')
		flag |= ROUT;
	else if (c == '|')
		flag |= PIPE;
	else if (c == '$')
		flag |= DOLLAR;
	else if (c == '~')
		flag |= TILDE;
	else if (c > 32)
		flag |= CHAR;
	return (flag);
}

void	ft_go(t_token *tkn)
{
	char	*tmp;
	int		tmp2;

	tmp = ft_substr(&tkn->str[tkn->prev], 0, tkn->curr - tkn->prev);
	tkn->prev = tkn->curr;
	if (ft_strncmp(tmp, " ", 1))
		ft_lstadd_back(&tkn->lst, ft_lstnew(tmp));
	else
		free(tmp);
	if (tkn->c_sta & (SINGLE_Q | DOUBLE_Q)
		&& tkn->p_sta & (SINGLE_Q | DOUBLE_Q))
	{
		tmp2 = tkn->p_sta & 0b000000011;
		tkn->p_sta ^= tmp2;
		tkn->c_sta ^= tmp2;
	}
}

t_token *ft_lex(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str, env);
	while(tkn->str && tkn->str[tkn->curr])
	{
		tkn->p_sta = ft_flag(tkn->str[tkn->prev]);
		tkn->c_sta = ft_flag(tkn->str[tkn->curr]);

		if (tkn->p_sta & (SINGLE_Q | DOUBLE_Q) || tkn->c_sta>>2 == tkn->p_sta>>2)
			tkn->curr++;
		else if (!(tkn->p_sta &(SINGLE_Q | DOUBLE_Q))
			&& (tkn->c_sta & SPCE || tkn->c_sta != tkn->p_sta))
			ft_go(tkn);
	}
	if (tkn->curr > tkn->prev + 1)
		ft_go(tkn);
	tmp_prtlst(tkn);
	ft_helplexer(tkn);
	if (!ft_redsyntax(tkn))
		return (NULL);
	return (tkn);
}
