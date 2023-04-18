/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:06:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 09:59:05 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_splitlist(t_cmd *cmd, t_env **env)
{
	t_token	*tkn;
	t_list	*lst;
	t_list	*copylst;
	int		i;
	int		j;

	copylst = NULL;
	tkn = ft_lexecho(cmd->str, *env);
	lst = tkn->lst;
	i = 0;
	j = 0;
	while (lst && i < cmd->count)
	{
		if (lst->content && ft_strchr((char *)lst->content, '|'))
			i++;
		lst = lst->next;
	}
	ft_helpsplitlist(lst, j, &copylst);
	ft_spoilecho(&copylst);
	ft_rmred(&copylst);
	ft_echoadjarr(copylst, &cmd->arr);
	ft_cleanlst(copylst);
	ft_cleantkn(tkn);
}

/* checks for redirectins and sets flags accordingly */
int	check_n(char **arr, t_cmd *cmd)
{
	int	i;

	i = 2;
	while (arr && arr[1] && arr[i] && ft_isvoption(arr[i]))
	{
		if (arr[i + 1] && !ft_strncmp(arr[i], " ", 2)
			&& ft_isvoption(arr[i + 1]))
			cmd->optn = 1;
		else if (arr[i + 1] && ft_strncmp(arr[i], " ", 2)
			&& !ft_strncmp(arr[i + 1], " ", 2))
			cmd->optn = 1;
		else if (arr[i + 1] && ft_strncmp(arr[i], " ", 2)
			&& ft_strncmp(arr[i + 1], " ", 2))
			break ;
		i++;
	}
	if (cmd->optn)
	{
		while (i > 2 && !ft_strncmp(arr[i], " ", 2))
			i--;
	}
	return (i);
}

/* checks for redirectins and sets flags accordingly */
void	check_redir(t_cmd *cmd)
{
	if (cmd->stat & FILE_KO)
		ft_fileissues(cmd->scmd);
	if (cmd->stat & RED_OK)
		ft_redirect(cmd->scmd);
	ft_noredirect(cmd->scmd);
}

/* imitates behaviour of bash echo, checking for option -n */
int	builtin_echo(t_cmd *cmd, t_env **env)
{
	int		i;
	char	**arr;

	check_redir(cmd);
	ft_splitlist(cmd, env);
	arr = cmd->arr;
	i = check_n(arr, cmd);
	while (arr && arr[1] && arr[i])
	{
		if (!ft_strncmp(arr[i], "$?", 3))
		{
			ft_putnbr_fd(g_exitstatus, 1);
			ft_putchar_fd('\n', 1);
			g_exitstatus = 0;
			return (EXIT_SUCCESS);
		}
		ft_putstr_fd(arr[i], 1);
		i++;
	}
	if (!cmd->optn)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
