/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:11:13 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/01 09:11:48 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(int argc, char **argv, t_env *env)
{
	int	i;
	t_env	*temp;
	char	*value;
	char	*var;

	i = 1;
	if (argc == 1)
	{
		print_env(env, true);
		return (0);
	}
	while (argc > 1 && argv[i])
	{
		temp = ret_var(env, argv[i]);
		if (temp)
		{
			value = get_var_content(argv[i]);
			var = get_var_name(argv[i]);
			upd_var(env, var, value);
		}
		i++;
	}
	print_env(env, false);
	return (0);
}