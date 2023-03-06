/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:15:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/06 19:13:23 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_countchars(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
			i += ft_strlen((char *)tmp->content);
		tmp = tmp->next;
	}
	return (i);
}

char	*ft_mergelist(t_list *var)
{
	t_list	*tmp;
	int		len;
	char	*str;

	len = ft_countchars(var);
	str = ft_calloc(len + 1, 1);
	if (!str)
		exit(1);
	tmp = var;
	len = 0;
	while (tmp)
	{
		ft_memcpy(&str[len], (char *)tmp->content, \
			ft_strlen((char *)tmp->content));
		len += ft_strlen((char *)tmp->content);
		tmp = tmp->next;
	}
	ft_cleanlst(var);
	return (str);
}

void	ft_helpstripsquotes(char **str, int *i, int *j, char **cont)
{
	*str = ft_calloc(ft_strlen(*cont), 1);
	if (!*str)
		exit(1);
	*i = 0;
	*j = 0;
	while ((*cont)[*i])
	{
		if (*cont[*i] != '\'')
		{
			*str[*j] = *cont[*i];
			(*j)++;
			(*i)++;
		}
		else
			(*i)++;
	}
	free(*cont);
	*cont = *str;
}

void	ft_stripsquotes(t_list *var)
{
	t_list	*tmp;
	char	*str;
	int		i;
	int		j;

	tmp = var;
	while (tmp)
	{
		if (tmp->content && ft_strchr((char *)tmp->content, '\''))
			ft_helpstripsquotes(&str, &i, &j, (char **)&tmp->content);
		tmp = tmp->next;
	}
}

void	ft_subenv(t_list *var, t_env *env)
{
	t_list	*tmp;
	t_env	*env_var;

	tmp = var;
	while (tmp)
	{
		if (((char *)tmp->content)[0] == '$' && ((char *)tmp->content)[1])
			env_var = ret_var(env, &((char *)tmp->content)[1]);
		free(tmp->content);
		if (env_var)
			tmp->content = ft_strdup(env_var->var_content);
		else
			tmp->content = NULL;
		tmp = tmp->next;
	}
}

void	ft_stripdquotes(t_list *var)
{
	t_list	*tmp;
	char	*str;

	tmp = var;
	while (tmp)
	{
		if (tmp->content && ft_strchr(tmp->content, '\"'))
		{
			str = ft_strtrim(tmp->content, "\"");
			free(tmp->content);
			tmp->content = str;
		}
		tmp = tmp->next;
	}
}

void	ft_helpprepexp(char *str, int *pos, int *st, t_list **var)
{
	if (str[pos[1]] == '\'')
		st[1] = st[1] ^ 0b01;
	else if (str[pos[1]] == '$' && !(st[1] & 0b01) && pos[1] != 0)
		st[1] = st[1] | 0b10;
	if (st[1] & 0b10 || ((st[0] & 0b01) != (st[1] & 0b01)))
	{
		ft_lstadd_back(var, \
			ft_lstnew(ft_substr(str, pos[0], pos[1] - pos[0])));
		st[0] = st[1];
		pos[0] = pos[1];
		st[1] &= 0b01;
	}
	pos[1]++;
}

t_list	*ft_prepexp(char *str)
{
	t_list	*var;
	int		pos[2];
	int		st[2];

	var = NULL;
	pos[0] = 0;
	pos[1] = 0;
	st[0] = 0b00;
	st[1] = 0b00;
	while (str && str[pos[1]])
		ft_helpprepexp(str, pos, st, &var);
	if (pos[1] > pos[0])
		ft_lstadd_back(&var, \
			ft_lstnew(ft_substr(str, pos[0], pos[1] - pos[0])));
	ft_stripdquotes(var);
	return (var);
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
		{
			tmp_str = ft_strtrim(tmp->content, "\'\"");
			free(tmp->content);
			tmp->content = tmp_str;
		}
		tmp = tmp->next;
	}
}

/* return t_list expanding system variables as appropriate */
void	ft_expand(t_token *tkn)
{
	t_list	*tmp;
	t_list	*var;
	int		flag;

	flag = 0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] != '\'' \
			&& ft_strchr(((char *)tmp->content), '$') && !flag)
		{
			var = ft_prepexp(tmp->content);
			ft_stripdquotes(var);
			ft_subenv(var, tkn->env);
			ft_stripsquotes(var);
			free(tmp->content);
			tmp->content = ft_mergelist(var);
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
