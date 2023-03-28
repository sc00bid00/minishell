/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:55:41 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/28 08:57:38 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_expdollar(t_token *tkn)
{
	t_list	*lst;
	char	*tmp;

	lst = tkn->lst;
	while (lst)
	{
		if (lst->content && ft_strchr((char *)lst->content, '$')
			&& ft_strlen((char *)lst->content) > 1)
		{
			if (((char *)lst->content)[0] == '$')
				tmp = ft_dollarsubst(&((char *)lst->content)[1], tkn);
			else if (!ft_strncmp((char *)lst->content, "\"$", 2))
				tmp = ft_putback(&((char *)lst->content)[2], "\"", "\"", tkn);
			else if (ft_strlen((char *)lst->content) > 2
				&& !ft_strncmp((char *)lst->content, "\"\'$", 3))
				tmp = ft_putback(&((char *)lst->content)[3], "\"\'", "\'\"", tkn);
			else if (ft_strchr((char *)lst->content, '$'))
				tmp = ft_otherprefix((char *)lst->content, tkn);
			else
				tmp = ft_strdup((char *)lst->content);
			free(lst->content);
			lst->content = tmp;
		}
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

char	*ft_otherprefix(char *str, t_token *tkn)
{
	char	*prefix;
	char	*tmp;
	int		i;

	prefix = ft_calloc(ft_strlen(str) + 1, 1);
	if (!prefix)
		exit (EXIT_FAILURE);
	i = 0;
	while (str && str[i] != '$')
	{
		prefix[i] = str[i];
		i++;
	}
	tmp = ft_strdup(ft_strchr(str, '$') + 1);
	str = ft_dollarsubst(tmp, tkn);
	free(tmp);
	tmp = ft_strjoin(prefix, str);
	free(str);
	free(prefix);
	return (tmp);
}

char	*ft_putback(char *str, char *set1, char *set2, t_token *tkn)
{
	char	*tmp;

	tmp = ft_strtrim(str, set1);
	str = ft_dollarsubst(tmp, tkn);
	free(tmp);
	tmp = ft_strjoin(set1, str);
	free(str);
	str = ft_strjoin(tmp, set2);
	free(tmp);
	return (str);
}
