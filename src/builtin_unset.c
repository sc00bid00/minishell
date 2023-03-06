/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/06 17:09:10 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	int i;

	i = 1;
	while(cmd->arr && cmd->arr[i])
	{
		if (ret_var(env, cmd->arr[i]) == NULL)
		{
			ft_error("unset", cmd->arr[i], NULL);
			return (0);
		}
		else
		{
			del_var(env, cmd->arr[i]);
			i++;
		}
	}
	return (0);
}
