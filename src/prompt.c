/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:33:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 08:23:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*read_line(void)
{
	char *line;
	line = readline("\033[36;1m$ \033[0m");
	if (line == NULL)
	{
		exit(1);
	}
	return (line);
}


int	get_input(void)
{
	char *input;

	exitstatus = 0;
	if ((input = read_line()) != NULL)
	{
		if (input && *input)
			add_history(input);
		free(input);
	}
	return (0);
}
