/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/14 17:26:16 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	tmp_prtlst(t_token *tkn)
{
	while (tkn->lst)
	{
		ft_printf("%s\n", tkn->lst->content);
		tkn->lst = tkn->lst->next;
	}
}

int	ft_init_tkn(t_token *tkn)
{
	tkn->lst = malloc(sizeof(t_list));
	if (!tkn->lst)
	{
		// ft_cleanup(tkn);
		return (0);
	}
	tkn->c_sta = 0b0000000;
	tkn->p_sta = 0b0000000;
	tkn->curr = 0;
	tkn->prev = 0;
	tkn->count = 0;
	return (1);
}

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

void	ft_save(t_token *tkn)
{
	t_list	*tmp;

	if (tkn->count == 0)
		tkn->lst->content = \
			ft_substr(tkn->str, tkn->prev, tkn->curr - tkn->prev);
	else
	{
		tmp = ft_lstnew(ft_substr(tkn->str, tkn->prev, tkn->curr - tkn->prev));
		ft_lstadd_back(&(tkn->lst), tmp);
	}
	tkn->count++;
}

void	ft_lex(t_token	*tkn)
{
	while (tkn->str && tkn->str[tkn->curr])
	{
		ft_getstatus(tkn);
		if (tkn->curr == 0)
			tkn->p_sta = tkn->c_sta;
		if (tkn->p_sta & 0b0000011)
			;
		else
		{
			if (tkn->c_sta != tkn->p_sta && tkn->p_sta != 0)
			{
				if (tkn->p_sta & 0b0000011)
					tkn->curr++;
				ft_save(tkn);
				tkn->prev = tkn->curr;
			}
			if (tkn->c_sta == 0)
				tkn->prev = tkn->curr + 1;
		}
		tkn->p_sta = tkn->c_sta;
		tkn->curr++;
	}
	if (!tkn->str[tkn->curr] && tkn->str[tkn->curr] != tkn->str[tkn->prev])
		ft_save(tkn);
}

int	main(void)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (1);
	if (!ft_init_tkn(tkn))
		return (1);
	tkn->str = " <   inf    cat| wc -l    |ls -la   | echo   \"so la la\" >>&out";
	ft_lex(tkn);
	tmp_prtlst(tkn);
	return (0);
}
