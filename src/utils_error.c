/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:57:28 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/06 15:49:10 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(char *s1, char *s2, char *mes)
{
	char *str;

	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd (s2, 2);
	ft_putstr_fd(": ", 2);
	if (!mes)
		str = strerror(errno);
	else
		str = mes;
	ft_putstr_fd(str, 2);
}
