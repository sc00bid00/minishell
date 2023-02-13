/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:53:09 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/13 19:00:50 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

/* return 0 initialized t_token */
int	ft_token_init(t_token *tkn)
{
	tkn->lst = malloc(sizeof(t_list));
	if (!tkn->lst)
		return (1);
	tkn->count = 0;
	tkn->curr = 0;
	tkn->prev = 0;
	tkn->chk = 0b000;
	return (0);
}

/* bit toggling to track open quotation marks */
void	ft_bitgate(t_token *tkn, char *str)
{
	if (str[tkn->curr] == '\'')
		tkn->chk = tkn->chk ^ 0b001;
	if (str[tkn->curr] == '\"')
		tkn->chk = tkn->chk ^ 0b010;
	if (str[tkn->curr] != ' ')
		tkn->chk = tkn->chk | 0b100;
}

/* return token splitting on space && multispace if no running quotes */
void ft_splitspace(t_token *tkn, char *str)
{
	t_list	*tmp;

	if (str[tkn->curr] == ' ' && !(tkn->chk & 0b011) && (tkn->chk & 0b100))
	{
		tkn->chk = tkn->chk ^ 0b100;
		if (tkn->count == 0)
			tkn->lst->content \
			= ft_substr(str, tkn->prev, tkn->curr - tkn->prev);
		else
		{
			tmp = \
				ft_lstnew(ft_substr(str, tkn->prev, tkn->curr - tkn->prev));
			ft_lstadd_back(&(tkn->lst), tmp);
		}
		tkn->count++;
		tkn->prev = tkn->curr + 1;
	}
}

/* return t_token with t_list of tokens */
void	ft_token(t_token *tkn, char *str)
{
	while (str && str[tkn->curr])
	{
		ft_bitgate(tkn, str);
		ft_splitspace(tkn, str);
		tkn->curr++;
	}
	if (!str[tkn->curr] && tkn->prev != tkn->curr)
		ft_lstadd_back(&(tkn->lst), \
		ft_lstnew(ft_substr(str, tkn->prev, tkn->curr - tkn->prev)));
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
	str = " <infile cat| wc -l  |ls -la   | echo \"so la la\" >>out";
	ft_token(tkn, str);
	while (tkn->lst)
	{
		ft_printf("%s\n", tkn->lst->content);
		tkn->lst = tkn->lst->next;
	}
	return (0);
}
