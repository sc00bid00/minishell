/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prexec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:58:03 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/26 12:59:06 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	ft_direct(t_list *tmp, int *count, t_scmd *scmd)
{
	if (tmp && ((char *)tmp->content)[0] == '<')
	{
		ft_isin(tmp, &count, scmd);
		tmp = tmp->next;
	}
	else if (tmp && ((char *)tmp->content)[0] == '>')
	{
		ft_isout(tmp, &count, scmd);
		tmp = tmp->next;
	}
	else if (tmp)
		ft_isword(tmp, count, scmd);
	return (1);
}

int	ft_prexec(t_scmd *scmd)
{
	t_list	*tmp;
	int		count;

	scmd->count = 0;
	while (scmd->arr && scmd->arr[scmd->count])
	{
		tmp = scmd->arr[scmd->count];
		count = ft_lstsize(tmp);
		while (tmp)
		{
			if (!ft_init_cmd(scmd))
				return (0);
			if (!ft_direct(tmp, &count, scmd))
				return (0);
			if (tmp)
				tmp = tmp->next;
		}
		scmd->count++;
	}
	return (1);
}
