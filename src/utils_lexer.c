/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:55:41 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/28 17:25:01 by lsordo           ###   ########.fr       */
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

char	*ft_putback(char *str, char *set1, char *set2)
{
	char	*tmp;

	tmp = ft_strjoin(set1, str);
	str = ft_strjoin(tmp, set2);
	free(tmp);
	return (str);
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

char	*ft_presuffix(char *str, t_token *tkn)
{
	char	*s[3];
	int		i[2];
	char	*tmp;

	s[0] = ft_calloc(ft_strlen(str) + 1, 1);
	s[1] = ft_calloc(ft_strlen(str) + 1, 1);
	s[2] = ft_calloc(ft_strlen(str) + 1, 1);
	i[0] = 0;
	i[1] = 0;
	while(str && str[i[0]] != '$')
		s[0][i[1]++] = str[i[0]++];
	i[1] = 0;
	while(str && str[i[0]] != ' ' && str[i[0]] != '\"')
		s[1][i[1]++] = str[i[0]++];
	i[1] = 0;
	while(str && str[i[0]])
		s[2][i[1]++] = str[i[0]++];
	tmp = ft_dollarsubst(&s[1][1], tkn);
	str = ft_putback(tmp, s[0], s[2]);
	free(tmp);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	return (str);
}
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
			else
			{
				if (((char *)lst->content)[0] == '\'')
					tmp = ft_strdup((char *)lst->content);
				else
					tmp = ft_presuffix((char *)lst->content, tkn);
			}
			free(lst->content);
			lst->content = tmp;
		}
		lst = lst->next;
	}
}
