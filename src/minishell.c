/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:56:35 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/28 15:00:15 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_exitstatus;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	signal(SIGQUIT, SIG_IGN);
	g_exitstatus = 0;
	env = copy_envp_to_env(envp);
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 2))
	{
		g_exitstatus = test_get_input(envp, &env, argv[2]);
		exit (g_exitstatus);
	}
	else
	{
		while (1)
		{
			setup_sigint();
			g_exitstatus = get_input(envp, &env);
		}
	}
	return (g_exitstatus);
}
