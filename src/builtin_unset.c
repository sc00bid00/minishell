/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/28 16:04:02 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_print_error(char *str)
{
	char	*copy;

	copy = ft_substr(str, 0, 2);
	ft_error(SHELL, "unset: ", copy, ERROR_10);
	ft_putendl_fd(ERROR_12, 2);
	g_exitstatus = 2;
	free (copy);
	return (2);
}

/*	imitates behavior of bash builtin unset, i.e. deletes the var from env*/
int	builtin_unset(t_cmd *cmd, t_env **env)
{
	int		i;
	int		j;

	i = 1;
	while (cmd->arr && cmd->arr[i])
	{
		j = 0;
		while (cmd->arr[i][j])
		{
			if (!ft_strncmp(&cmd->arr[i][0], "-", 1))
				return (ms_print_error(cmd->arr[i]));
			if (!ft_isalpha(cmd->arr[i][j]) && (cmd->arr[i][j] != '_'))
			{
				ft_error(SHELL, "unset: ", cmd->arr[i], ERROR_4);
				g_exitstatus = 1;
				return (1);
			}
			else
				(*env) = del_var(env, cmd->arr[i]);
			j++;
		}
		i++;
	}
	return (0);
}
