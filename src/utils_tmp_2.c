/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tmp_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:13:07 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/02 12:12:07 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tmp_prtarray(char **arr)
{
	int	i;

	ft_putendl_fd("=== checkin  debug - tmp_prtarray ===", 2);
	i = 0;
	while (arr && arr[i])
	{
		ft_putstr_fd(arr[i], 2);
		ft_putendl_fd("$", 2);
		i++;
	}
	ft_putendl_fd("=== checkout debug - tmp_prtarray ===", 2);
}
