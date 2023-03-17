/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:04 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/17 11:53:00 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	if argument is cd without additional parameter, return home directory */
char	*get_dir(t_cmd *cmd, t_env *env)
{
	char	*dir;
	t_env	*temp;
	
	(void)	env;
	int i;

	i = 0;
	// while (cmd->arr[i])
	// {
	// 	printf("arg is %s\n", cmd->arr[i]);
	// 	i++;	
	// }
	if (cmd->arr && cmd->arr[1] == NULL)
	{
		temp = ret_var(env, "HOME");
		dir = temp->var_content;
	}
	// else if (cmd->arr && cmd->arr[2] == NULL && !ft_strncmp(cmd->arr[1], "-", 2))
	// {
	// 	temp =	ret_var(env, "OLDPWD");
	// 	dir =	temp->var_content;
	// }
	else
		dir = cmd->arr[1];
	printf("directory is: %s\n", dir);
	return (dir);
}

/*	set value from OLDPWD to PWD and get new value for PWD */
void	update_pwd(t_env *env)
{
	char	*cwd;
	char	*str;
	t_env	*temp;

	cwd = getcwd(NULL, 0);
	// printf("CWD is %s\n", cwd);
	temp = ret_var(env, "PWD");
	str = temp->var_content;
	// printf("PWD is %s\n", str);
	if (str)
	{
		if (!upd_var(env, "OLDPWD", str))
			ft_error("cd: ", "PWD: ", ERROR_1);
	}
	else
		printf("ERROR\n");
	if (!upd_var(env, "PWD", cwd))
		printf("ERROR\n");
	free (cwd);
}

/*	use chdir function to change dir */
int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char *dir;

	dir = get_dir(cmd, env);

	if (dir == NULL)
	{
		ft_error("minishell: ", dir, ERROR_2);
		return (ERROR);
	}
	if (chdir(dir) == ERROR)
	{
		printf("%s\n", dir);
		ft_error("cd", cmd->arr[0], NULL);
		return (ERROR);
	}
	update_pwd(env);
	// //test_print
	// char *pwd;
	// char *oldpwd;
	// t_env *temp;
	// t_env *temp2;
	// temp = ret_var(env, "PWD");
	// pwd = temp->var_content;
	// printf("PWD is %s\n", pwd);
	// temp2 = ret_var(env, "OLDPWD");
	// if (temp2)
	// {
	// 	oldpwd = temp2->var_content;
	// 	printf("OLDPWD is %s\n", oldpwd);
	// }
	return (EXIT_SUCCESS);
}
