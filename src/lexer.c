/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/28 16:50:15 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_spoillist(t_token *tkn)
{
	t_list	*tmp;
	t_list	*copy;
	char	*tmps;

	copy = NULL;
	tmp = tkn->lst;
	while (tkn->lst)
	{
		if (tmp->content && (!ft_strncmp(tmp->content, "\'\'", 3)
			|| !ft_strncmp(tmp->content, "\"\"", 3)))
			tmps = NULL;
		else if (tmp->content && ((char *)tmp->content)[0] == '\"')
			tmps = ft_strtrim((char *)tmp->content, "\"");
		else if (tmp->content && ((char *)tmp->content)[0] == '\'')
			tmps = ft_strtrim((char *)tmp->content, "\'");
		else if (tkn->lst->content)
			tmps = ft_strdup((char *)tkn->lst->content);
		tmp = tkn->lst->next;
		free(tkn->lst->content);
		free(tkn->lst);
		if (tmps)
			ft_lstadd_back(&copy, ft_lstnew(tmps));
		tkn->lst = tmp;
	}
	tkn->lst = copy;
}

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

t_token *ft_lex(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str, env);
	tkn->c_sta = ft_flag(tkn->str[0]);
	while(tkn->str && tkn->str[tkn->curr])
	{
		tkn->curr++;
		if (!(tkn->c_sta & SOME_Q) && ft_flag(tkn->str[tkn->curr]) != tkn->c_sta)
			ft_go(tkn);
		else if ((tkn->c_sta & SOME_Q) && ((tkn->c_sta & SOME_Q) == (ft_flag(tkn->str[tkn->curr]) & SOME_Q)))
			tkn->c_sta ^= (ft_flag(tkn->str[tkn->curr]) & SOME_Q);
	}
	if (tkn->curr > tkn->prev + 1)
		ft_go(tkn);
	tmp_prtlst(tkn);
	ft_expdollar(tkn);
	tmp_prtlst(tkn);
	ft_exptilde(tkn);
	ft_spoillist(tkn);
	if (!ft_redsyntax(tkn))
		return (NULL);
	return (tkn);
}
