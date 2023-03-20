/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:05:53 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/20 17:00:29 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	print array for control purposes */
void	print_env_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		printf("%s\n", env_array[i]);
		i++;
	}
}

/*	create array from list for execve */
char	**create_env_array(t_env *env)
{
	char	**env_array;
	int		i;
	int		size;

	i = 0;
	size = ms_lstsize(env);
	env_array = calloc(size + 1, sizeof(env_array));
	if (!env_array)
		return (NULL);
	while (env)
	{
		env_array[i] = ms_multijoin(env->var_name, '=', env->var_content);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
