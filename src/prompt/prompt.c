/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:33:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/16 13:32:36 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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