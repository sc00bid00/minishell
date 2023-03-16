/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:56:09 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/16 12:11:13 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_builtin(t_scmd *scmd)
{
	int i = 0;
	// printf("string is: %s\n",scmd->cmd[i]->arr[0]);
	if (!ft_strncmp(scmd->cmd[i]->arr[0], "echo", 4))
	{
		builtin_echo(*scmd->cmd, scmd->env);
		return (1);
	}
	else	
		return (0);
}