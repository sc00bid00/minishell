/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:50:40 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 16:43:29 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <signals.h>
# include <env.h>
# include <lexer.h>
# include <parser.h>
# include <utils.h>
# include <builtin.h>
# include <executor.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <get_next_line.h>
# include <prompt.h>

/* define error */
# define ERROR 		-1

/* define colors */
# define BOLD		"\x01\033[1m\x02"
# define BLACK		"\x01\033[30;1m\x02"
# define RED		"\x01\033[31;1m\x02"
# define GREEN		"\x01\033[32;1m\x02"
# define YELLOW		"\x01\033[33;1m\x02"
# define BLUE		"\x01\033[34;1m\x02"
# define MAGENTA	"\x01\033[35;1m\x02"
# define CYAN		"\x01\033[36;1m\x02"
# define WHITE		"\x01\033[37;1m\x02"
# define RESET		"\x01\033[0m;\x02"

/*	need to declare extern int g_exitstatus in order to comply with
	linux compiler as well */
extern int	g_exitstatus;

#endif
