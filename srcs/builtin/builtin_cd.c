/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:04 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/27 14:24:59 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	if argument is cd (argc == 1) or cd ~, return home directory */
char	*get_dir(int argc, char **argv, t_env *env)
{
	char	*dir;
	
	if (argc == 1 || (argc == 2 && ft_strncmp(argv[1], "~", 2)))
		dir = return_var_content(env, "HOME");
	else if (argc == 2 && ft_strncmp(argv[1], "-", 2))
		dir = return_var_content(env, "OLDPWD");
	else if (argv[1])
		dir = argv[1];
	return (dir);
}

/*	set value from OLDPWD to PWD and get new value for PWD */
void	update_pwd(t_env *env)
{
	char	*cwd;
	char	*str;
	
	cwd = getcwd(NULL, 0);
	str = return_var_content(env, "PWD");
	if (str)
	{
		if (!update_variable(env, "OLDPWD", str))
			ft_error("cd", 1, "PWD");
	}
	else
		printf("ERROR\n");
	if (!update_variable(env, "PWD", cwd))
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
		ft_error("minishell", 1, 0);
		return (ERROR);
	}	
	if (chdir(dir) == ERROR)
	{
		ft_error("cd", 0, argv[1]);
		return (ERROR);
	}
	update_pwd(env);
	char *pwd;
	char *oldpwd;
	pwd = return_var_content(env, "PWD");
	oldpwd = return_var_content(env, "OLDPWD");
	printf("PWD is %s\n", pwd);
	printf("OLDPWD is %s\n", oldpwd);
	return (EXIT_SUCCESS);
}
