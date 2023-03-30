/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:06:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/30 09:12:15 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isvoption(char *str)
{
	int	i;

	if (str && ft_strncmp(str, "-n", 2))
		return (0);
	i = 1;
	while (str && str[i])
	{
		if (str[i] != 'n')
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
	ft_spoillist(tkn);
	return (tkn);
}

int	builtin_echo(t_cmd *cmd, t_env **env)
{
	t_token	*tkn;
	t_list	*lst;
	int		optn;
	int		i;
	int		j;

	tkn = ft_lexecho(cmd->str, *env);
	optn = 0;
	i = 1;
	if (cmd->arr && !cmd->arr[i])
		ft_putchar_fd('\n', 1);
	else if (cmd->arr && !ft_strncmp(cmd->arr[i], "$?", 3))
	{
		ft_putnbr_fd(g_exitstatus, 1);
		ft_putchar_fd('\n', 1);
		g_exitstatus = 0;
		return (EXIT_SUCCESS);
	}
	while (cmd->arr && cmd->arr[i] && ft_isvoption(cmd->arr[i]))
	{
		optn = 1;
		i++;
	}
	j = 0;
	lst = tkn->lst;
	while (lst)
	{
		if (j > i)
		{
			if (j == i + 1 && !ft_strncmp((char *)lst->content, " ", 2))
				;
			else
			{
				if (ft_allspaces((char *)lst->content))
					ft_putchar_fd(' ', 1);
				else
					ft_putstr_fd((char *)lst->content, 1);
			}
		}
		lst = lst->next;
		j++;
	}
	if (!optn)
		ft_putchar_fd('\n', 1);
	ft_cleantkn(tkn);
	return (EXIT_SUCCESS);
}
