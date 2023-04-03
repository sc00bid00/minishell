/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:04:40 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/03 14:05:07 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helplsttostr(t_list *tmplst, int *i)
{
	while (tmplst)
	{
		if (tmplst->content)
			*i += ft_strlen((char *)tmplst->content);
		tmplst = tmplst->next;
	}
}
