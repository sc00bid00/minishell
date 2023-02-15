/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 14:01:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

/* return t_list trimming external ' "*/
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

/* return t_list expanding system variables */
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

/* clear t_token allocation */
void	ft_cleanup(t_token *tkn)
{
	t_list	*tmp;

	if (tkn->lst)
	{
		while (tkn->lst)
		{
			tmp = tkn->lst->next;
			free(tkn->lst->content);
			free(tkn->lst);
			tkn->lst = tmp;
		}
	}
	if (tkn)
		free(tkn);
}

/* print lst->content to stdout */
void	tmp_prtlst(t_token *tkn)
{
	t_list	*tmp;

	tmp = tkn->lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

/* return 0ed t_token elements */
void	ft_init_tkn(t_token *tkn)
{
	tkn->lst = NULL;
	tkn->c_sta = 0b0000000;
	tkn->p_sta = 0b0000000;
	tkn->curr = 0;
	tkn->prev = 0;
	tkn->count = 0;
}

/* return flags bitwise current character */
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

/* return t_list node with char * token as content */
void	ft_save(t_token *tkn)
{
	ft_lstadd_back(&(tkn->lst), \
		ft_lstnew(ft_substr(tkn->str, tkn->prev, tkn->curr - tkn->prev)));
	tkn->count++;
}

/* return t_token with t_list of tokens
token is either a word or a metacharacter
text in quotes is word */
void	ft_lex(t_token *tkn)
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

/* main for test purpose*/
int	main(void)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (1);
	ft_init_tkn(tkn);
	tkn->str \
		= "\"$USER\" <   inf    cat '$USER'| wc -l << $USER $PATH \"PATH\" << end  |ls -la   \
		| echo   \"so la la\" >>out";
	ft_printf("\ninput string:\n%s\n**********\n", tkn->str);
	ft_lex(tkn);
	ft_printf("\ntoken list before expansion:\n**********\n");
	tmp_prtlst(tkn);
	ft_expand(tkn);
	ft_printf("\ntoken list before quotation marks removal:\n**********\n");
	tmp_prtlst(tkn);
	ft_remquotes(tkn);
	ft_printf("\nfinal token list :\n**********\n");
	tmp_prtlst(tkn);
	ft_printf("**********\nchained list with %d nodes\n", tkn->count);
	ft_cleanup(tkn);
	return (0);
}
