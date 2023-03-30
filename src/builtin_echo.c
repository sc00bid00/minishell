/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:14:00 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/29 22:15:14 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*ft_splitlist(char *str)
{
	t_list	*tmplst;
	int		p;
	int		i;
	int		flag;

	tmplst = NULL;
	p = 0;
	i = 0;
	flag = 0;
	while (str && str[p])
	{
		if (ft_flag(str[p]) & SOME_Q)
			flag ^= ft_flag(str[p]);
		if (!flag && (str[p] == '|' || str[p] == ' '))
		{
			ft_lstadd_back(&tmplst, ft_lstnew(ft_substr(str, i, p - i)));
			i = p;
		}
		p++;
	}
	if (p > i + 1)
		ft_lstadd_back(&tmplst, ft_lstnew(ft_substr(str, i, p)));
	return (tmplst);
}

int	builtin_echo(t_cmd *cmd, t_env **env)
{
	t_list	*tmplst;

	(void)env;
	tmplst = NULL;
	tmplst = ft_splitlist(cmd->str);
	tmp_prtlst2(tmplst);
	return (0);
}

int	ft_isvoption(char *str)
{
	int	i;

	if (str && ft_strncmp(str, "-n", 2))
		return (0);
	i = 1;
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// int	builtin_echo(t_cmd *cmd, t_env **env)
// {
// 	int	i;
// 	int	optn;

// 	(void)env;
// 	optn = 0;
// 	i = 1;
// 	if (cmd->arr && !cmd->arr[i])
// 		ft_putchar_fd('\n', 1);
// 	else if (cmd->arr && !ft_strncmp(cmd->arr[i], "$?", 3))
// 	{
// 		ft_putnbr_fd(g_exitstatus, 1);
// 		ft_putchar_fd('\n', 1);
// 		g_exitstatus = 0;
// 		return (EXIT_SUCCESS);
// 	}
// 	while (cmd->arr && cmd->arr[i] && ft_isvoption(cmd->arr[i]))
// 	{
// 		optn = 1;
// 		i++;
// 	}
// 	while (cmd->arr && cmd->arr[i])
// 	{
// 		ft_putstr_fd(cmd->arr[i], 1);
// 		if (cmd->arr[i + 1] && cmd->arr[i + 1][0] != '\0')
// 			ft_putchar_fd(' ', 1);
// 		i++;
// 	}
// 	if (!optn)
// 		ft_putchar_fd('\n', 1);
// 	g_exitstatus = 0;
// 	return (EXIT_SUCCESS);
// }
