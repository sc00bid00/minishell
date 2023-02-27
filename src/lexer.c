/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 17:15:53 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/* return t_list without ' and/or " */
void	ft_remquotes(t_token *tkn)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content)
			tmp_str = ft_strtrim(tmp->content, "\'\"");
		free(tmp->content);
		tmp->content = tmp_str;
		tmp = tmp->next;
	}
}

/* return t_list expanding system variables as appropriate */
void	ft_expand(t_token *tkn)
{
	t_list	*tmp;
	char	*tmp_str;
	int		flag;

	flag = 0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] != '\'' \
			&& ft_strchr(((char *)tmp->content), '$') && !flag)
		{
			tmp_str = ft_strtrim((char *)tmp->content, "\"$");
			free(tmp->content);
			tmp->content = ft_strdup(getenv(tmp_str));
			free(tmp_str);
		}
		if (!ft_strncmp((char *)tmp->content, "<<", 2) && !flag)
			flag = 1;
		else
			flag = 0;
		tmp = tmp->next;
	}
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

/* return t_token with t_list of tokens
token is either a word or a metacharacter
text in quotes is word */
t_token	*ft_lex(char *str)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str);
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
				ft_save(tkn);
			if (tkn->c_sta == 0)
				tkn->prev = tkn->curr + 1;
		}
		tkn->p_sta = tkn->c_sta;
		tkn->curr++;
	}
	if (!tkn->str[tkn->curr] && tkn->str[tkn->curr] != tkn->str[tkn->prev])
		ft_save(tkn);
	ft_expand(tkn);
	ft_remquotes(tkn);
	return (tkn);
}
