/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:12:27 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/03 14:14:30 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exec_fork(t_scmd *scmd)
{
	while (scmd && scmd->cmd && scmd->cmd[scmd->count])
	{
		if (pipe(scmd->fd) == -1)
			exit(EXIT_FAILURE);
		scmd->id = fork();
		if (scmd->id == -1)
			exit(EXIT_FAILURE);
		if (scmd->id == 0)
			ft_child(scmd);
		else
			ft_parent(scmd);
		scmd->count++;
	}
}
