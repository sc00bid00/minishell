/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redsyntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:04:50 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/16 18:48:47 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_syntaxerror(t_token *tkn, char *str)
{
	ft_eerr("minishell: syntax error near unexpected token `", str, "\'");
	ft_cleantkn(tkn);
	return (NULL);
}

void	ft_helpistoken(char ***t)
{
	*t = ft_calloc(6, sizeof(char *));
	if (!*t)
		exit (EXIT_FAILURE);
	(*t)[0] = "<";
	(*t)[1] = "<<";
	(*t)[2] = ">";
	(*t)[3] = ">>";
	(*t)[4] = "|";
}

int	ft_istoken(void *content)
{
	char	**t;
	int		i;
	int		m;

	ft_helpistoken(&t);
	i = 0;
	while (t[i])
	{
		m = ft_strlen(t[i]);
		if (ft_strlen(content) > (size_t)m)
			m = ft_strlen(content);
		if (content && !ft_strncmp((char *)content, t[i], m))
		{
			free(t);
			return (1);
		}
		i++;
	}
	free(t);
	return (0);
}

t_token	*ft_redsyntax(t_token *tkn)
{
	t_list	*tmp;
	int		flag;

	flag = 0b0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (flag && ft_istoken(tmp->content))
			return (ft_syntaxerror(tkn, (char *)tmp->content));
		else if (flag && !ft_istoken(tmp->content))
			flag ^= 1;
		if (ft_istoken(tmp->content))
			flag |= 1;
		tmp = tmp->next;
	}
	if (flag)
		return (ft_syntaxerror(tkn, "newline"));
	return (tkn);
}
