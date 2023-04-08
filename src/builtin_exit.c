/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:37:51 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/08 08:15:31 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* check if input is numeric to decide if error message is needed */
bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/*	checks for numeric and non numeric parameters */
/*	checks for number of paramters */
int	builtin_exit(t_cmd *cmd, t_env **env)
{
	(void)env;
	ft_putendl_fd("exit", 2);
	if (cmd->arr && cmd->arr[1] != NULL)
	{
		if (!is_numeric(cmd->arr[1]))
		{
			ft_error(SHELL, "line 0: exit: ", cmd->arr[1], ERROR_2);
			g_exitstatus = 255;
		}
		else if (cmd->arr[2] == NULL)
			g_exitstatus = ft_atoi_long_long(cmd->arr[1]) % 256;
		else if (cmd->arr[2] != NULL)
		{
			ft_error(SHELL, NULL, cmd->arr[0], ERROR_3);
			g_exitstatus = 1;
			return (EXIT_FAILURE);
		}
	}
	ms_mycleanup(cmd, env);
	return (g_exitstatus);
}

/* modified atoi to take 19 digits input for g_exitstatus like bash*/
unsigned long long	ft_atoi_long_long(char *str)
{
	unsigned long long	num;
	long				sign;
	char				*copy;

	copy = str;
	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = 10 * num + *str - '0';
		if ((num > INT64_MAX && sign == -1)
			|| (num > INT64_MAX - 1 && sign == 1))
			return (ft_error(SHELL, "line 0: exit: ", copy, ERROR_2), 255);
		str++;
	}
	return (sign * num);
}
