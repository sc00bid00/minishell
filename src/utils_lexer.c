/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:55:41 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/29 10:11:00 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exptilde(t_token *tkn)
{
	t_list	*lst;
	t_env	*env_var;
	char	*tmp;
	int		i;

	tmp = NULL;
	lst = tkn->lst;
	i = 0;
	while (lst)
	{
		if (lst->content && !ft_strncmp((char *)lst->content, "|", 1))
			i = -1;
		if (i < 2 && lst->content && ft_strchr((char *)lst->content, '~')
			&& ft_strlen((char *)lst->content) > 1)
		{
			if (((char *)lst->content)[1] == '/')
			{
				env_var = ret_var(tkn->env, "HOME");
				if (env_var && env_var->var_content)
					tmp = ft_strjoin(env_var->var_content, &((char *)lst->content)[1]);
				free(lst->content);
				lst->content = tmp;
			}
		}
		else if (i < 2 && lst->content && !ft_strncmp((char *)lst->content, "~", 1))
		{
			env_var = ret_var(tkn->env, "HOME");
			if (env_var && env_var->var_content)
			{
				free(lst->content);
				lst->content = ft_strdup(env_var->var_content);
			}
		}
		i++;
		lst = lst->next;
	}
}


char	*ft_dollarsubst(char *str, t_token *tkn)
{
	t_env	*env_var;
	char	*tmp;

	tmp = NULL;
	if (str && str[0] == '0')
	{
		env_var = ret_var(tkn->env, "SHELL");
		if (env_var)
			tmp = ft_strjoin(env_var->var_content, &str[1]);
	}
	else if (str)
	{
		env_var = ret_var(tkn->env, str);
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
	while (tmplst)
	{
		if (tmplst->content)
			i += ft_strlen((char *)tmplst->content);
		tmplst = tmplst->next;
	}
	tmp = ft_calloc(i + 1, 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	i = 0;
	tmplst = lst;
	while (tmplst)
	{
		j = 0;
		while (tmplst->content && ((char *)tmplst->content)[j])
			tmp[i++] = ((char*)tmplst->content)[j++];
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
			tmp = ft_dollarsubst(&((char *)tmplst->content)[1], tkn);
			free(tmplst->content);
			tmplst->content = tmp;
		}
		tmplst = tmplst->next;
	}
	return (tmplst);
}

// t_list	*ft_strtolst(char *str)
// {
// 	/* wip Kathrin */
// }

void	ft_expdollar(t_token *tkn)
{
	t_list	*lst;
	t_list	*tmplst;
	char	*tmp;

	lst = tkn->lst;
	while (lst)
	{
		if (lst->content && ft_strchr((char *)lst->content, '$')
			&& ft_strlen((char *)lst->content) > 1
			&& ((char *)lst->content)[0] != '\'')
		{
			// tmplst = ft_strtolst((char *)lst->content);
			tmplst = ft_moddollar(tmplst, tkn);
			tmp = ft_lsttostr(tmplst);
			free(lst->content);
			lst->content = tmp;
		}
		lst = lst->next;
	}
}
