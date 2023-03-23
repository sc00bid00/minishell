/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tmp_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:13:07 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/23 12:13:20 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tmp_prtarray(char **arr)
{
	int	i;

	ft_putendl_fd("Start debug - tmp_prtarray", 2);
	i = 0;
	while (arr && arr[i])
	{
		ft_putendl_fd(arr[i], 2);
		i++;
	}
	ft_putendl_fd("tmp_prtarray - end debug", 2);
}

