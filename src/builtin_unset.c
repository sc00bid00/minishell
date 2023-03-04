/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 13:19:14 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	int i;

	i = 0;
	while(cmd->arr && cmd->arr[i])
	{
		if (ret_var(env, cmd->arr[i]) == NULL)
		{
			ft_error("unset", cmd->arr[i], 0);
			return (0);
		}
		else
		{
			del_var(env, cmd->arr[i]);
			i++;
		}
	}
	print_env(env, false);
	return (0);
}
