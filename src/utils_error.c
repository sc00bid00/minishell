/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:57:28 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 16:29:36 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(char *s1, char *s2, char *mes)
{
	char	*str;

	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(": ", 2);
	if (!mes)
		str = strerror(errno);
	else
		str = mes;
	ft_putendl_fd(str, 2);
	g_exitstatus = 127;
}

void	ft_eerr(void *fst_msg, void *snd_msg, void *trd_msg)
{
	ft_putstr_fd((char *)fst_msg, STDERR_FILENO);
	ft_putstr_fd((char *)snd_msg, STDERR_FILENO);
	ft_putendl_fd((char *)trd_msg, STDERR_FILENO);
}
