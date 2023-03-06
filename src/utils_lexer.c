/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:15:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/06 11:02:14 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		if (!ft_strncmp(tmp->content, ">", 1) \
		|| !ft_strncmp(tmp->content, "<", 1))
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
	t_env	*env_var;
	char	*tmp_str;
	int		flag;

	flag = 0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] != '\'' \
			&& ft_strchr(((char *)tmp->content), '$') && !flag)
		{
			// tmp_str = ft_strtrim((char *)tmp->content, "\"$");
			env_var = ret_var(tkn->env, ft_strtrim((char *)tmp->content, "\"$"));
			tmp_str = env_var->var_content;
			printf("%s\n", tmp_str);
			// free(tmp->content);
			// tmp->content = ft_strdup(getenv(tmp_str));
			// free(tmp_str);
		}
		if (!ft_strncmp((char *)tmp->content, "<<", 2) && !flag)
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
