/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:04 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/04 20:39:16 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	if argument is cd without additional parameter, return home directory */
/*	if parameter is "-", return OLD PWD */
char	*get_dir(t_cmd *cmd, t_env **env)
{
	char	*dir;
	t_env	*temp;

	dir = NULL;
	if (cmd->arr && cmd->arr[1] == NULL)
	{
		temp = ret_var(env, "HOME");
		if (temp)
			dir = temp->var_content;
	}
	else if (cmd->arr && !ft_strncmp(cmd->arr[1], "-", 2))
	{
		temp = ret_var(env, "OLDPWD");
		if (temp)
			dir = temp->var_content;
		else
		{
			ft_error(SHELL, cmd->arr[0], NULL, ERROR_15);
			g_exitstatus = 1;
			dir = getcwd(NULL, 0);
		}
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
	str = NULL;
	if (!temp)
		new_var("PWD");
	else
		str = temp->var_content;
	if (str)
	{
		if (!upd_var(env, "OLDPWD", str))
			return (free(cwd), EXIT_FAILURE);
	}
	else
		return (free(cwd), EXIT_FAILURE);
	if (!upd_var(env, "PWD", cwd))
		return (free(cwd), EXIT_FAILURE);
	free(cwd);
	return (EXIT_SUCCESS);
}

/*	use chdir function to change dir */
int	builtin_cd(t_cmd *cmd, t_env **env)
{
	char	*dir;
	char	*pwd;

	dir = get_dir(cmd, env);
	if (cmd && cmd->arr && chdir(dir) == ERROR)
	{
		ft_error(SHELL, "line 0: cd: ", cmd->arr[1], NULL);
		g_exitstatus = 1;
		return (EXIT_FAILURE);
	}
	else
		update_pwd(env);
	pwd = getcwd(NULL, 0);
	if (cmd->arr && cmd->arr[1] && !ft_strncmp(cmd->arr[1], "-", 2)
		&& ft_my_strcmp(pwd, dir))
		printf("%s\n", pwd);
	g_exitstatus = 0;
	free (pwd);
	return (EXIT_SUCCESS);
}
