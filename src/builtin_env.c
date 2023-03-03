/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:50:57 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/01 16:38:42 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	print environment list */
int	print_env(t_env *env)
{
	if (!env)
		return (ERROR);
	while (env != NULL)
	{
		if (env->var_name)
		{
			printf("%s", env->var_name);
			printf("=");
		}
		if(env->var_content)
			printf("%s\n", env->var_content);
		if (env->next)
			env = env->next;
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

/*	imitate behavior of env */
int	builtin_env(int argc, char **argv, t_env *env)
{
	(void) argc;
	(void) argv;
	if (!print_env(env))
		return (ERROR);
	return (EXIT_SUCCESS);
}
