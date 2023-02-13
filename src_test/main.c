/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:53:09 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/13 17:08:36 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	ft_chkquoting(t_token *tkn, char *str)
{

}

void	ft_func(t_token *tkn, char *str)
{
	t_list	*tmp;

	while (str && str[tkn->curr])
	{
		if (str[tkn->curr] == '\'')
			tkn->chk = tkn->chk ^ 0b01;
		if (str[tkn->curr] == '\"')
			tkn->chk = tkn->chk ^ 0b10;
		if (str[tkn->curr] == ' ' && tkn->chk == 0)
		{
			if (tkn->count == 0)
				tkn->lst->content = ft_substr(str, tkn->prev, tkn->curr - tkn->prev);
			else
			{
				tmp = ft_lstnew(ft_substr(str, tkn->prev, tkn->curr - tkn->prev));
				ft_lstadd_back(&(tkn->lst), tmp);
			}
			tkn->count++;
			tkn->prev = tkn->curr + 1;
		}
		tkn->curr++;
	}
	if (!str[tkn->curr] && tkn->prev != tkn->curr)
		ft_lstadd_back(&(tkn->lst), ft_lstnew(ft_substr(str, tkn->prev, tkn->curr - tkn->prev)));
}

/* 	chk = 01	'	opened
	chk = 10	"	opened */

int		ft_token_init(t_token *tkn)
{
	tkn->lst = malloc(sizeof(t_list));
	if (!tkn->lst)
		return (1);
	tkn->count = 0;
	tkn->curr = 0;
	tkn->prev = 0;
	tkn->chk = 0b00;
	return (0);
}

int	main(void)
{
	t_token	*tkn;
	char	*str;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (1);
	if (ft_token_init(tkn))
		return (1);
	str = "\"< infile hallo\" cat -e | grep b | grep x | wc -l > outfile";
	ft_func(tkn, str);
	while (tkn->lst)
	{
		ft_printf("%s\n", tkn->lst->content);
		tkn->lst = tkn->lst->next;
	}
	return (0);
}
