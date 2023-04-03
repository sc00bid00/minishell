/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:46:23 by lsordo          #+#    #+#             */
/*   Updated: 2023/04/03 13:46:24 by lsordo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_expdollarecho(t_token *tkn)
{
	t_list	*lst;
	t_list	*tmplst;
	t_list	*tmplst2;
	char	*tmp;

	lst = tkn->lst;
	while (lst)
	{
		if (lst->content && ft_strchr((char *)lst->content, '$')
			&& ft_strlen((char *)lst->content) > 1
			&& ((char *)lst->content)[0] != '\'')
		{
			tmplst = ft_strtolstecho((char *)lst->content);
			tmplst2 = ft_moddollar(tmplst, tkn);
			tmp = ft_lsttostr(tmplst2);
			ft_cleanlst(tmplst);
			free(lst->content);
			lst->content = tmp;
		}
		lst = lst->next;
	}
	ft_remspcnul(&tkn->lst);
}

void	ft_goecho(t_token *tkn)
{
	char	*tmp;

	tmp = ft_substr(&tkn->str[tkn->prev], 0, tkn->curr - tkn->prev);
	tkn->prev = tkn->curr;
	ft_lstadd_back(&tkn->lst, ft_lstnew(tmp));
	tkn->c_sta = ft_flag(tkn->str[tkn->curr]);
}

void	ft_lex_util(t_token *tkn)
{
	if (ft_flag(tkn->str[tkn->curr]) & DOLLAR
		&& ft_flag(tkn->str[tkn->curr + 1]) & CHAR)
	{
		tkn->curr++;
		while (ft_flag(tkn->str[tkn->curr]) & CHAR)
					tkn->curr++;
	}
	ft_goecho(tkn);
}

t_token	*ft_lexecho(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str, env);
	tkn->c_sta = ft_flag(tkn->str[0]);
	while (tkn->str && tkn->str[tkn->curr])
	{
		tkn->curr++;
		if (!(tkn->c_sta & SOME_Q)
			&& ft_flag(tkn->str[tkn->curr]) != tkn->c_sta)
			ft_lex_util(tkn);
		else if ((tkn->c_sta & SOME_Q)
			&& ((tkn->c_sta & SOME_Q) == (ft_flag(tkn->str[tkn->curr])
					& SOME_Q)))
			tkn->c_sta ^= (ft_flag(tkn->str[tkn->curr]) & SOME_Q);
	}
	if (tkn->curr > tkn->prev + 1)
		ft_goecho(tkn);
	ft_expdollarecho(tkn);
	ft_exptilde(tkn);
	return (tkn);
}
