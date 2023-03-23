/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_remquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:51:43 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/23 16:13:34 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helpremquotes(char *dst, char *str)
{
	int	i;
	int	j;
	int	flag;

	flag = 0b00;
	i = 0;
	j = 0;
	while (str && str[i])
	{

		if ((str[i] == '"' && !(flag & 0b10)) || (str[i] == '\'' && !(flag & 0b01)))
		{
			if (str[i]== '"')
				flag ^= 0b01;
			else
				flag ^= 0b10;
			i++;
		}
		else
		{
			dst[j] = str[i];
			j++;
			i++;
		}
	}
}

void	ft_remquotes(t_token *tkn)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && (ft_strchr((char *)tmp->content, '"') \
			|| ft_strchr((char *)tmp->content, '\'')))
		{
			tmp_str = ft_calloc(ft_strlen((char *)tmp->content), 1);
			if (!tmp_str)
				exit(1);
			ft_helpremquotes(tmp_str, (char *)tmp->content);
			if (tmp->content)
			{
				free(tmp->content);
				tmp->content = tmp_str;
			}
		}
		tmp = tmp->next;
	}
}
