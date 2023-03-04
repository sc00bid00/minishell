/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:56:35 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/04 11:09:20 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int exitstatus;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_token	*tkn;
	t_scmd	*scmd;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	/* reduce lines: can we move this loop to signals.c? */
	while (1)
	{
		setup_sigint();
		get_input();
	}
	env = copy_env_to_heap(envp);
	tkn
	return (0);
}
