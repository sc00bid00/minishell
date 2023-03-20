/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/20 12:48:02 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	imitates behavior of bash builtin unset, i.e deletes the var from env*/
int	builtin_unset(t_cmd *cmd, t_env *env)
{
	int i;

	i = 1;
	printf(("TEST\n"));
	while(cmd->arr && cmd->arr[i])
	{
		if (!ret_var(env, cmd->arr[i]))
		{
			ft_error("unset", cmd->arr[i], NULL);
			i++;
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
