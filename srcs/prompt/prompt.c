/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:33:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/14 15:33:42 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_line(void)
{
	char *line;
	line = readline("\033[36;1m$ \033[0m");
	if (line == NULL)
	{
		printf("Error reading line.\n");
		exit(1);
	}
	return (line);
}


int	get_input(void)
{
	char *input;
	if ((input = read_line()) != NULL)
	{
		if (input && *input)
			add_history(input);
		free(input);
	}
	return (0);
}