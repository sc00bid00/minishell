/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:57:28 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/03 12:48:32 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *s1, char *s2, int i)
{
	char *str;

	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd (s2, 2);
	ft_putstr_fd(": ", 2);
	if (i == 0)
		str = strerror(errno);
	else
		str = "meine Fehlermeldung";
	ft_putstr_fd(str, 2);
}