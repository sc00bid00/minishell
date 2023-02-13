/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:40 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/13 17:52:54 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define ERROR_1	"Error: Error reading line.\n"

# define	BOLD	"\x01\033[1m"
# define	BLACK	"\x01\033[30;1m"
# define	RED		"\x01\033[31;1m"
# define	GREEN	"\x01\033[32;1m"
# define	YELLOW	"\x01\033[33;1m"
# define	BLUE	"\x01\033[34;1m"
# define	MAGENTA	"\x01\033[35;1m"
# define	CYAN	"\x01\033[36;1m"
# define	WHITE	"\x01\033[37;1m"
# define	RESET	"\x01\033[0m;"

// read input

char	*read_line(void);
int		get_input(void);

#endif