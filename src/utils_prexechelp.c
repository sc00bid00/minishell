/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prexechelp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:33:28 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/20 10:48:49 by lsordo           ###   ########.fr       */
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

void	ft_helpisheredoc(t_scmd	*scmd, t_cmd **tmp)
{
	char	tmp_s[2];

	tmp_s[0] = 65 + scmd->count;
	tmp_s[1] = '\0';
	(*tmp)->in_name = ft_strjoin("/var/tmp/.hdoc_", tmp_s);
	(*tmp)->fd_in = open((*tmp)->in_name, O_RDWR | O_CREAT, 0644);
}
