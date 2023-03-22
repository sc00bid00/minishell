/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:37:51 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 08:45:07 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* modified atoi to take 19 digits input for exitstatus like bash*/
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
int	builtin_exit(t_cmd *cmd, t_env *env)
{
	(void)env;

	ft_putendl_fd("exit", 2);
	if (cmd->arr && cmd->arr[1] != NULL)
	{
		if(!is_numeric(cmd->arr[1]))
		{
			ft_error("minishell: exit: ", cmd->arr[1], ERROR_2);
			exitstatus = 255;
		}
		else if (cmd->arr[2] == NULL)
			exitstatus = ft_atoi_long_long(cmd->arr[1]) % 256;
		else if (cmd->arr[2] != NULL)
		{
			ft_error("minishell: ", cmd->arr[0], ERROR_3);
			exitstatus = 1;
			return (EXIT_FAILURE);
		}
	}
	printf("Exitstatus is:%d\n", exitstatus);
	ft_clean_env(env);
	exit (exitstatus);
}

/* modified atoi to take 19 digits input for exitstatus like bash*/
unsigned long long	ft_atoi_long_long(char *str)
{
	unsigned long long	num;
	int					sign;

	if (str == NULL)
		return (0);
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
		if (sign < 0)
			return (0);
		if (sign > 0)
			return (-1);
		num = 10 * num + *str - '0';
		str++;
	}
	return (sign * num);
}
