/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 16:29:36 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	imitates behavior of bash builtin unset, i.e. deletes the var from env*/
int	builtin_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->arr && cmd->arr[i])
	{
		if (!ft_isalpha(cmd->arr[i][0]))
		{
			ft_error("minishell: unset: ", cmd->arr[i], ERROR_4);
			g_exitstatus = 1;
		}
		else
			(*env) = del_var(env, cmd->arr[i]);
		i++;
	}
	return (0);
}
