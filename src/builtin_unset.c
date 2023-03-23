/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 17:35:57 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	if variable is not in env head, delete node, else call separate function*/
t_env	*remove_var(char *str, t_env **env)
{
	if (!ft_my_strcmp ((*env)->var_name, str))
	{
		(*env) = del_first_var(env);
		printf("FIRST_VAR\n");
	}
	else
		(*env) = del_var(env, str);
	return (*(env));
}

/*	imitates behavior of bash builtin unset, i.e. deletes the var from env*/
int	builtin_unset(t_cmd *cmd, t_env **env)
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
			(*env) = remove_var(cmd->arr[i], env);
		i++;
	}
	return (0);
}
