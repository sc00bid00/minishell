/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/20 14:35:42 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	if variable is not in env head, delete node, else call separate function*/
void	remove_var(char *str, t_env *env)
{
	if (!strncmp (env->var_name, str, ft_strlen(env->var_name)))
	{
		del_first_var(&env);
		print_env(env, false);
	}
	else
		del_var(env, str);
}

/*	imitates behavior of bash builtin unset, i.e. deletes the var from env*/
int	builtin_unset(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 1;
	while (cmd->arr && cmd->arr[i])
	{
		if (!ft_isalpha(cmd->arr[i][0]))
		{
			ft_error("minishell: unset: ", cmd->arr[i], ERROR_4);
			exitstatus = 1;
		}
		else
			remove_var(cmd->arr[i], env);
		i++;
	}
	printf("%s\n", env->var_name);
	return (0);
}
