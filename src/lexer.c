/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/03 14:43:45 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_allspaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_flag(char c)
{
	int		flag;

	flag = 0;
	if (c == '\'')
		flag ^= SINGLE_Q;
	else if (c == '"')
		flag ^= DOUBLE_Q;
	else if (c == ' ')
		flag |= SPCE;
	else if (c == '<')
		flag |= RIN;
	else if (c == '>')
		flag |= ROUT;
	else if (c == '|')
		flag |= PIPE;
	else if (c > 32)
		flag |= CHAR;
	return (flag);
}

void	ft_go(t_token *tkn)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(&tkn->str[tkn->prev], 0, tkn->curr - tkn->prev);
	tkn->prev = tkn->curr;
	if (!ft_allspaces(tmp))
	{
		tmp2 = ft_strtrim(tmp, " ");
		free(tmp);
		ft_lstadd_back(&tkn->lst, ft_lstnew(tmp2));
	}
	else
		free(tmp);
	tkn->c_sta = ft_flag(tkn->str[tkn->curr]);
}

void	ft_lex_uti(t_token *tkn)
{
	if (ft_flag(tkn->str[tkn->curr]) & DOLLAR
		&& ft_flag(tkn->str[tkn->curr + 1]) & CHAR)
	{
		tkn->curr++;
		while (ft_flag(tkn->str[tkn->curr]) & CHAR)
			tkn->curr++;
	}
	ft_go(tkn);
}

t_token	*ft_lex(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str, env);
	tkn->c_sta = ft_flag(tkn->str[0]);
	while (tkn->str && tkn->str[tkn->curr])
	{
		tkn->curr++;
		if (!(tkn->c_sta & SOME_Q)
			&& ft_flag(tkn->str[tkn->curr]) != tkn->c_sta)
			ft_lex_uti(tkn);
		else if ((tkn->c_sta & SOME_Q)
			&& ((tkn->c_sta & SOME_Q) == (ft_flag(tkn->str[tkn->curr])
					& SOME_Q)))
			tkn->c_sta ^= (ft_flag(tkn->str[tkn->curr]) & SOME_Q);
	}
	if (tkn->curr > tkn->prev + 1)
		ft_go(tkn);
	ft_expdollar(tkn);
	ft_exptilde(tkn);
	ft_spoillist(tkn);
	if (!ft_redsyntax(tkn))
		return (NULL);
	return (tkn);
}
