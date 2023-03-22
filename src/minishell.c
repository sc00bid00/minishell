/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:56:35 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/22 15:19:43 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exitstatus;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	signal(SIGQUIT, SIG_IGN);
	exitstatus = 0;
	env = copy_envp_to_env(envp);
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 2))
	{
		exitstatus = test_get_input(envp, env, argv[2]);
		exit (exitstatus);
	}
	else
	{
		while (1)
		{
			setup_sigint();
			exitstatus = get_input(envp, env);
		}
	}
	return (exitstatus);
}
