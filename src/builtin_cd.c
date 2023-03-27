/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:04 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 16:29:36 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	if argument is cd without additional parameter, return home directory */
/*	if parameter is "-", return OLD PWD */
char	*get_dir(t_cmd *cmd, t_env **env)
{
	char	*dir;
	t_env	*temp;

	if (cmd->arr && cmd->arr[1] == NULL)
	{
		temp = ret_var(env, "HOME");
		dir = temp->var_content;
	}
	else if (cmd->arr && !ft_strncmp(cmd->arr[1], "-", 2))
	{
		temp = ret_var(env, "OLDPWD");
		if (temp)
			dir = temp->var_content;
		else
			dir = getcwd(NULL, 0);
	}
	else
		dir = cmd->arr[1];
	return (dir);
}

/*	set value OLDPWD = PWD and get new value for PWD */
int	update_pwd(t_env **env)
{
	char	*cwd;
	char	*str;
	t_env	*temp;

	cwd = getcwd(NULL, 0);
	temp = ret_var(env, "PWD");
	if (!temp)
		new_var("PWD");
	str = temp->var_content;
	if (str)
	{
		if (!upd_var(env, "OLDPWD", str))
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	if (!upd_var(env, "PWD", cwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*	use chdir function to change dir */
int	builtin_cd(t_cmd *cmd, t_env **env)
{
	char	*dir;

	dir = get_dir(cmd, env);
	if (cmd && cmd->arr && chdir(dir) == ERROR)
	{
		ft_error("minishell: cd: ", cmd->arr[1], NULL);
		g_exitstatus = 1;
		return (EXIT_FAILURE);
	}
	else
		update_pwd(env);
	if (cmd->arr && !ft_strncmp(cmd->arr[1], "-", 2))
		printf("%s\n", getcwd(NULL, 0));
	g_exitstatus = 0;
	return (EXIT_SUCCESS);
}
