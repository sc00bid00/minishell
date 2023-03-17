/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:50:57 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/06 15:10:45 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	print environment list */
int	print_env(t_env *env, bool ex)
{
	if (!env)
		return (ERROR);
	while (env != NULL)
	{
		if (env->var_name)
		{
			if (ex)
				printf("declare -x ");
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
