/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:06:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/30 15:45:24 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isdquote(char *str)
{
	if (!ft_strncmp(str, "\"\"", 3) || !ft_strncmp(str, "\'\'", 3))
		return (1);
	return (0);
}

void	ft_spoilecho(t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	while (*lst && ft_isdquote((*lst)->content))
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	tmp = *lst;
	while(tmp && tmp->next)
	{
		while (ft_isdquote(tmp->next->content))
		{
			tmp2 = tmp->next->next;;
			free(tmp->next->content);
			free(tmp->next);
			tmp->next = tmp2;
		}
		tmp = tmp->next;
	}
}

int	ft_isvoption(char *str)
{
	int	i;

	i = 2;
	if (str && (ft_strncmp(str, "-n", 2) || str[i] != ' '))
		return (0);
	while (str && str[i])
	{
		if (str[i] != 'n' || str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/* splits the string according to $ to send to expansion */
t_list	*ft_strtolstecho(char *str)
{
	t_list	*lst;
	int		i;
	int		j;

	lst = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, i - j)));
			j = i;
		}
		i++;
	}
	if (i != j)
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, i - j)));
	return (lst);
}

void	ft_expdollarecho(t_token *tkn)
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
			tmplst = ft_strtolstecho((char *)lst->content);
			tmplst = ft_moddollar(tmplst, tkn);
			tmp = ft_lsttostr(tmplst);
			free(lst->content);
			lst->content = tmp;
		}
		lst = lst->next;
	}
}

void	ft_goecho(t_token *tkn)
{
	char	*tmp;

	tmp = ft_substr(&tkn->str[tkn->prev], 0, tkn->curr - tkn->prev);
	tkn->prev = tkn->curr;
	ft_lstadd_back(&tkn->lst, ft_lstnew(tmp));
	tkn->c_sta = ft_flag(tkn->str[tkn->curr]);
}

t_token *ft_lexecho(char *str, t_env *env)
{
	t_token	*tkn;

	tkn = ft_init_tkn(str, env);
	tkn->c_sta = ft_flag(tkn->str[0]);
	while(tkn->str && tkn->str[tkn->curr])
	{
		tkn->curr++;
		if (!(tkn->c_sta & SOME_Q) && ft_flag(tkn->str[tkn->curr]) != tkn->c_sta)
		{
			if (ft_flag(tkn->str[tkn->curr]) & DOLLAR
				&& ft_flag(tkn->str[tkn->curr + 1]) & CHAR)
			{
				tkn->curr++;
				while (ft_flag(tkn->str[tkn->curr]) & CHAR)
					tkn->curr++;
			}
			ft_goecho(tkn);
		}
		else if ((tkn->c_sta & SOME_Q) && ((tkn->c_sta & SOME_Q) == (ft_flag(tkn->str[tkn->curr]) & SOME_Q)))
			tkn->c_sta ^= (ft_flag(tkn->str[tkn->curr]) & SOME_Q);
	}
	if (tkn->curr > tkn->prev + 1)
		ft_goecho(tkn);
	ft_expdollarecho(tkn);
	ft_exptilde(tkn);
	return (tkn);
}

t_list	*ft_splitlist(t_cmd *cmd, t_env **env)
{
	t_token	*tkn;
	t_list	*lst;
	t_list	*copylst;
	int		i;

	copylst = NULL;
	tkn = ft_lexecho(cmd->str, *env);
	lst = tkn->lst;
	i = 0;
	while (lst)
	{
		if (lst->content && ft_strchr((char *)lst->content, '|'))
			i++;
		if (i == cmd->count && !ft_strchr((char *)lst->content, '|'))
		{
			if (!ft_strncmp((char *)lst->content, " ", 2)
			&& lst->next && !ft_strncmp((char *)lst->next->content, "echo", 5))
				;
			else if (ft_allspaces((char *)lst->content))
				ft_lstadd_back(&copylst, ft_lstnew(ft_strdup(" ")));
			else
				ft_lstadd_back(&copylst, ft_lstnew(ft_strdup(lst->content)));
		}
		lst = lst->next;
	}
	ft_spoilecho(&copylst);
	ft_cleantkn(tkn);
	return (copylst);
}

int	builtin_echo(t_cmd *cmd, t_env **env)
{
	t_list	*lst;
	// int		optn;
	// int		i;

	// optn = 0;
	lst = ft_splitlist(cmd, env);
	// i = 2;
	tmp_prtlst2(lst);
	ft_cleanlst(lst);
	return (EXIT_SUCCESS);
}

