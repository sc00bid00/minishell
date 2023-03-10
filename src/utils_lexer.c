/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:15:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/10 14:46:01 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_expandtilde(t_token *tkn)
{
	t_list	*tmp;
	t_env	*env_var;

	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && !ft_strncmp((char *)tmp->content, "~", \
			ft_strlen((char *)tmp->content)))
		{
			env_var = ret_var(tkn->env, "HOME");
			free(tmp->content);
			if (env_var)
				tmp->content = ft_strdup(env_var->var_content);
			else
				tmp->content = ft_strdup(getenv("HOME"));
		}
		tmp = tmp->next;
	}
}

void	ft_helpunextkn(t_token *tkn, t_list *tmp)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(tmp->content, 2);
	write (2, "\'\n", 2);
	ft_cleantkn(tkn);
}

/* return NULL if unexpected token found */
t_token	*ft_unextkn(t_token *tkn)
{
	t_list	*tmp;
	int		token;

	token = 0b0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && (!ft_strncmp(tmp->content, ">", 1) \
		|| !ft_strncmp(tmp->content, "<", 1)))
		{
			if (token & 1)
			{
				ft_helpunextkn(tkn, tmp);
				return (NULL);
			}
			else
				token |= 1;
		}
		else
			token &= 0;
		tmp = tmp->next;
	}
	return (tkn);
}

/* return t_list expanding system variables as appropriate */
void	ft_expand(t_token *tkn)
{
	t_list	*tmp;
	t_list	*new;
	int		flag;

	flag = 0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (!flag && tmp->content && ((char *)tmp->content)[0] != '\'' \
			&& (ft_strchr(((char *)tmp->content), '$') \
				|| ft_strchr(((char *)tmp->content), '~')))
		{
			new = NULL;
			ft_explode(&new, (char *)tmp->content);
			ft_substitute(&new, tkn->env);
			ft_reassemble(new, &tmp);
			ft_cleanlst(new);
			ft_expandtilde(tkn);
		}
		if (tmp->content && !ft_strncmp((char *)tmp->content, "<<", 2) && !flag)
			flag = 1;
		else
			flag = 0;
		tmp = tmp->next;
	}
}

void	ft_helplexer(t_token *tkn)
{
	if (!tkn->str[tkn->curr] && tkn->str[tkn->curr] != tkn->str[tkn->prev])
		ft_save(tkn);
	ft_expand(tkn);
	ft_remquotes(tkn);
}
