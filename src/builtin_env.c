/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:50:57 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 13:07:26 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	print environment list */
int	print_env(t_env *env, bool export)
{
	if (!env)
		return (ERROR);
	while (env != NULL)
	{
		if (export)
			printf("declare -x ");
		if (env->var_name)
		{
			printf("%s", env->var_name);
			if (env->var_content)
				printf("=");
			else
				printf("\n");
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
int	builtin_env(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	if (!print_env(env, false))
		return (ERROR);
	return (EXIT_SUCCESS);
}
