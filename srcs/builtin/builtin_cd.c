/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:04 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/24 15:36:24 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ~ . ..  */

void	update_pwd(t_env *env)
{
	char	*cwd;
	char	*str;
	
	cwd = getcwd(NULL, 0);
	str = return_var_content(env, "PWD");
	update_variable(env, "OLDPWD", str);
	update_variable(env, "PWD", cwd);
	free (cwd);
}

t_env	*builtin_cd(int argc, char **argv, t_env *env)
{
	if (argc == 1)
	{
		if (chdir("~"))
			printf("Failed to change directory\n");
	}
		
	
	// if (chdir("/Users/kczichow/Documents/projects") == 0) {
    //     printf("Changed directory to /home/myusername/mydirectory\n");
    // } else {
    //     printf("Failed to change directory\n");
    // }
	update_pwd(env);
	
	// print_env(env);
	
		// print_env(env);
	// free (cwd);
	// free (str);
	// free (temp);
	// (~)
	// .
	// ..
	// src 
	
	// chdir(".") = chdir ("path")
	// cd src 
	// cd ./src 
	// cd ../minishell/src 
	// cd /bin/

	// free OLDPWD
	// OLDPWD = PWD 
	// PWD = getcwd
	return (env);
}

/*
	export:
	- keine Argumente : print everything
	- bestehende Argumente: ipdate oder ignore
	- neue Argumente: add;
*/