/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:04 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 08:23:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	if argument is cd (argc == 1) or cd ~, return home directory */
char	*get_dir(int argc, char **argv, t_env *env)
{
	char	*dir;
	t_env	*temp;

	if (argc == 1 || (argc == 2 && ft_strncmp(argv[1], "~", 2)))
	{
		temp = ret_var(env, "HOME");
		dir = temp->var_content;
	}
	else if (argc == 2 && ft_strncmp(argv[1], "-", 2))
	{
		temp =	ret_var(env, "OLDPWD");
		dir =	temp->var_content;
	}
	else
		dir = argv[1];
	// printf("%s\n", dir);
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
			ft_error("cd", "PWD", 1);
	}
	else
		printf("ERROR\n");
	if (!upd_var(env, "PWD", cwd))
		printf("ERROR\n");
	free (cwd);
}

/*	use chdir function to change dir */
int	builtin_cd(int argc, char **argv, t_env *env)
{
	char *dir;

	dir = get_dir(argc, argv, env);

	if (dir == NULL)
	{
		ft_error("minishell", dir, 1);
		return (ERROR);
	}
	if (chdir(dir) == ERROR)
	{
		printf("%s\n", dir);
		ft_error("cd", argv[1], 0);
		return (ERROR);
	}
	update_pwd(env);
	//test_print
	char *pwd;
	char *oldpwd;
	t_env *temp;
	t_env *temp2;
	temp = ret_var(env, "PWD");
	pwd = temp->var_content;
	printf("PWD is %s\n", pwd);
	temp2 = ret_var(env, "OLDPWD");
	if (temp2)
	{
		oldpwd = temp2->var_content;
		printf("OLDPWD is %s\n", oldpwd);
	}
	return (EXIT_SUCCESS);
}
