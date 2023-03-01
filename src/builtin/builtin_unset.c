/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/01 16:39:16 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(int argc, char **argv, t_env *env)
{
	int i;

	(void) argc;
	i = 1;
	while(argv[i])
	{
		if (ret_var(env, argv[i]) == NULL)
		{
			ft_error("unset", argv[i], 0);
			return (0);
		}
		else
		{
			del_var(env, argv[i]);
			i++;
		}
	}
	print_env(env);
	return (0);
}