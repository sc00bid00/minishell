/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:14:44 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/28 08:37:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_spoillist(t_token *tkn)
{
	t_list	*tmp;
	t_list	*copy;
	char	*tmps;

	copy = NULL;
	tmp = tkn->lst;
	while (tkn->lst)
	{
		if (tmp->content && (!ft_strncmp(tmp->content, "\'\'", 3)
			|| !ft_strncmp(tmp->content, "\"\"", 3)))
			tmps = NULL;
		else if (tmp->content && ((char *)tmp->content)[0] == '\"')
			tmps = ft_strtrim((char *)tmp->content, "\"");
		else if (tmp->content && ((char *)tmp->content)[0] == '\'')
			tmps = ft_strtrim((char *)tmp->content, "\'");
		else
			tmps = ft_strdup((char *)tkn->lst->content);
		tmp = tkn->lst->next;
		free(tkn->lst->content);
		free(tkn->lst);
		if (tmps)
			ft_lstadd_back(&copy, ft_lstnew(tmps));
		tkn->lst = tmp;
	}
	tkn->lst = copy;
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

/* return t_list nodes containing tokne char * */
void	ft_save(t_token *tkn)
{
	ft_lstadd_back(&(tkn->lst), \
		ft_lstnew(ft_substr(tkn->str, tkn->prev, tkn->curr - tkn->prev)));
	tkn->prev = tkn->curr;
	tkn->count++;
}

int	ft_allspaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_flag(char c)
{
	int		flag;

	flag = 0;
	if (c == '\'')
		flag ^= SINGLE_Q;
	else if (c == '"')
		flag ^= DOUBLE_Q;
	else if (c == ' ')
		flag |= SPCE;
	else if (c == '<')
		flag |= RIN;
	else if (c == '>')
		flag |= ROUT;
	else if (c == '|')
		flag |= PIPE;
	else if (c > 32)
		flag |= CHAR;
	return (flag);
}

void	ft_go(t_token *tkn)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(&tkn->str[tkn->prev], 0, tkn->curr - tkn->prev);
	tkn->prev = tkn->curr;
	if (!ft_allspaces(tmp))
	{
		tmp2 = ft_strtrim(tmp, " ");
		free(tmp);
		ft_lstadd_back(&tkn->lst, ft_lstnew(tmp2));
	}
	else
		free(tmp);
	tkn->c_sta = ft_flag(tkn->str[tkn->curr]);

}

t_token *ft_lex(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str, env);
	tkn->c_sta = ft_flag(tkn->str[0]);
	while(tkn->str && tkn->str[tkn->curr])
	{
		tkn->curr++;
		if (!(tkn->c_sta & SOME_Q) && ft_flag(tkn->str[tkn->curr]) != tkn->c_sta)
			ft_go(tkn);
		else if ((tkn->c_sta & SOME_Q) && ((tkn->c_sta & SOME_Q) == (ft_flag(tkn->str[tkn->curr]) & SOME_Q)))
			tkn->c_sta ^= (ft_flag(tkn->str[tkn->curr]) & SOME_Q);
	}
	if (tkn->curr > tkn->prev + 1)
		ft_go(tkn);
	tmp_prtlst(tkn);
	ft_expdollar(tkn);
	ft_exptilde(tkn);
	ft_spoillist(tkn);
	tmp_prtlst(tkn);
	// ft_helplexer(tkn);
	if (!ft_redsyntax(tkn))
		return (NULL);
	return (tkn);
}
