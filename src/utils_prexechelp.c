/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prexechelp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:33:28 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/16 18:34:13 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helppaths(t_cmd *cmd, char **arr, int j)
{
	char	*tmp;

	tmp = ft_strjoin(arr[j], "/");
	cmd->path = ft_strjoin(tmp, cmd->arr[0]);
	free(tmp);
}
