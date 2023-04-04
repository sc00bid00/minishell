/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:15:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 19:47:55 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_dollarsubst(char *str, t_token *tkn)
{
	t_env	*env_var;
	char	*tmp;

	tmp = NULL;
	if (str && str[0] == '0')
	{
		env_var = ret_var(&tkn->env, "SHELL");
		if (env_var)
			tmp = ft_strjoin(env_var->var_content, &str[1]);
	}
	else if (str && ft_isdigit(str[0]))
		tmp = ft_strdup(&str[1]);
	else if (str && str[0] == '?')
		tmp = ft_itoa(g_exitstatus);
	else if (str)
	{
		env_var = ret_var(&tkn->env, str);
		if (env_var)
			tmp = ft_strdup(env_var->var_content);
	}
	return (tmp);
}

char	*ft_lsttostr(t_list *lst)
{
	t_list	*tmplst;
	char	*tmp;
	int		i;
	int		j;

	tmplst = lst;
	i = 0;
	ft_helplsttostr(tmplst, &i);
	tmp = ft_calloc(i + 1, 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	i = 0;
	tmplst = lst;
	while (tmplst)
	{
		j = 0;
		while (tmplst->content && ((char *)tmplst->content)[j] != '\0')
			tmp[i++] = ((char *)tmplst->content)[j++];
		tmplst = tmplst->next;
	}
	return (tmp);
}

t_list	*ft_moddollar(t_list *lst, t_token *tkn)
{
	t_list	*tmplst;
	char	*tmp;

	tmplst = lst;
	while (tmplst)
	{
		if (tmplst->content && ((char *)tmplst->content)[0] == '$')
		{
			if (((char *)tmplst->content)[1])
			{
				tmp = ft_dollarsubst(&((char *)tmplst->content)[1], tkn);
				free(tmplst->content);
				tmplst->content = tmp;
			}
		}
		tmplst = tmplst->next;
	}
	return (lst);
}

/* splits the string according to $ to send to expansion */
t_list	*ft_strtolst(char *str)
{
	t_list	*lst;
	int		i;
	int		j;

	lst = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '?' && str[i] != '_' && i != 0)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, i - j)));
			j = i;
		}
		i++;
	}
	if (i != j && str[j] != '\0')
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, i - j)));
	tmp_prtlst2(lst);
	return (lst);
}

void	ft_expdollar(t_token *tkn)
{
	t_list	*lst;
	char	*tmp;
	int		flag;

	lst = tkn->lst;
	flag = 0;
	while (lst)
	{
		if (lst->content && !ft_strncmp(lst->content, "<<", 3))
			flag = 1;
		if (!flag && lst->content && ft_strchr((char *)lst->content, '$')
			&& ft_strlen((char *)lst->content) > 1
			&& ((char *)lst->content)[0] != '\'')
		{
			ft_helpexpdollar(&tmp, lst, tkn);
			free(lst->content);
			lst->content = tmp;
		}
		if (flag && lst->content && ft_strncmp(lst->content, "<<", 3))
			flag = 0;
		lst = lst->next;
	}
}
