/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:56:09 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 14:43:24 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	(*ft_builtin(t_scmd *scmd))(t_cmd *cmd, t_env **env)
{
	int	(*fun)(t_cmd *, t_env **);

	if (!scmd->cmd[scmd->count] || !scmd->cmd[scmd->count]->arr
		|| !scmd->cmd[scmd->count]->arr[0])
		return (NULL);
	if (!ft_strncmp(scmd->cmd[scmd->count]->arr[0], "exit", 4))
		fun = &builtin_exit;
	else if (!ft_strncmp(scmd->cmd[scmd->count]->arr[0], "echo", 5))
		fun = &builtin_echo;
	else if (!ft_strncmp(scmd->cmd[scmd->count]->arr[0], "cd", 2))
		fun = &builtin_cd;
	else if (!ft_strncmp(scmd->cmd[scmd->count]->arr[0], "unset", 5))
		fun = &builtin_unset;
	else if (!ft_strncmp(scmd->cmd[scmd->count]->arr[0], "pwd", 3))
		fun = &builtin_pwd;
	else if (!ft_strncmp(scmd->cmd[scmd->count]->arr[0], "env", 3))
		fun = &builtin_env;
	else if (!ft_strncmp(scmd->cmd[scmd->count]->arr[0], "export", 6))
		fun = &builtin_export;
	else
		return (NULL);
	scmd->cmd[scmd->count]->builtin = 1;
	return (fun);
}
