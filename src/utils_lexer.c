/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:15:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/24 10:59:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isquote(char c1, char c2)
{
	if ((c1 == '\'' && c2 == '\'') || (c1 == '"' && c2 == '"'))
		return (1);
	return (0);
}

void	*ft_quotepairs(char *str)
{
	char	*newstr;
	int		i;
	int		j;

	newstr = ft_calloc(ft_strlen(str) + 1, 1);
	if (!newstr)
		exit(EXIT_FAILURE);
	j = 0;
	i = 0;
	while (str && str[i] && str[i + 1])
	{
		if (ft_isquote(str[i], str[i + 1]))
			i += 2;
		else
		{
			newstr[j] = str[i];
			j++;
			i++;
		}
	}
	newstr[j] = str[i];
	free(str);
	return (newstr);
}

int	ft_iscapital(int c)
{
	if ((c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

void	ft_expandtilde(t_token *tkn)
{
	t_list	*tmp;
	t_env	*env_var;

	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && !ft_strncmp((char *)tmp->content, "~", 1))
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
		if (tmp->content)
			tmp->content = ft_quotepairs((char *)(tmp->content));
		if (!flag && tmp->content && ((char *)tmp->content)[0] != '\'' \
			&& (ft_strchr(((char *)tmp->content), '$') \
				|| ft_strchr(((char *)tmp->content), '~')))
		{
			new = NULL;
			ft_explode(&new, (char *)tmp->content);
			ft_substitute(&new, tkn->env);
			ft_reassemble(new, &tmp);
			ft_cleanlst(new);
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
