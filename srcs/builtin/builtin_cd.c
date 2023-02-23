/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:04 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/23 16:36:24 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ~ . ..  */
void	builtin_cd(void)
{
	(~)
	.
	..
	src 
	
	chdir(".") = chdir ("path")
	cd src 
	cd ./src 
	cd ../minishell/src 
	cd /bin/

	free OLDPWD
	OLDPWD = PWD 
	PWD = getcwd
}

/*
	export:
	- keine Argumente : print everything
	- bestehende Argumente: ipdate oder ignore
	- neue Argumente: add;
*/