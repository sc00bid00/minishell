/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/22 17:00:22 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* return t_list nodes containing tokne char * */
void	ft_save(t_token *tkn)
{
	if (tkn->p_sta & 0b0000011)
		tkn->curr++;
	ft_lstadd_back(&(tkn->lst), \
		ft_lstnew(ft_substr(tkn->str, tkn->prev, tkn->curr - tkn->prev)));
	tkn->prev = tkn->curr;
	tkn->count++;
}

/* return bitwise flags to split tokens */
void	ft_getstatus(t_token *tkn)
{
	if (tkn->str[tkn->curr] == '\'')
		tkn->c_sta = tkn->c_sta ^ 0b0000001;
	else if (tkn->str[tkn->curr] == '\"')
		tkn->c_sta = tkn->c_sta ^ 0b0000010;
	else
	{
		tkn->c_sta = tkn->c_sta & 0b0000011;
		if (tkn->str[tkn->curr] == '|')
			tkn->c_sta = tkn->c_sta | 0b0000100;
		else if (tkn->str[tkn->curr] == '>')
			tkn->c_sta = tkn->c_sta | 0b0001000;
		else if (tkn->str[tkn->curr] == '<')
			tkn->c_sta = tkn->c_sta | 0b0010000;
		else if (tkn->str[tkn->curr] == '&')
			tkn->c_sta = tkn->c_sta | 0b0100000;
		else if (tkn->str[tkn->curr] > 32)
			tkn->c_sta = tkn->c_sta | 0b1000000;
	}
}

/* return t_token with t_list of tokens
token is either a word or a metacharacter
text in quotes is word */
t_token	*ft_lex(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str, env);
	while (tkn->str && tkn->str[tkn->curr])
	{
		ft_getstatus(tkn);
		if (tkn->curr == 0)
			tkn->p_sta = tkn->c_sta;
		if (tkn->c_sta & 0b0000011)
			;
		else if (!(tkn->c_sta & 0b0000011) && !(tkn->p_sta & 0b0000001))
		{
			if ((tkn->c_sta >> 2) != (tkn->p_sta >> 2) && tkn->p_sta != 0)
				ft_save(tkn);
			if (tkn->c_sta == 0)
				tkn->prev = tkn->curr + 1;
		}
		tkn->p_sta = tkn->c_sta;
		tkn->curr++;
	}
	ft_helplexer(tkn);
	if (!ft_redsyntax(tkn))
		return (NULL);
	return (tkn);
}
