/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 08:50:56 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/20 17:03:49 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	SIGINT = Ctrl + C;
*	SIGQUIT = Ctrl \
*	Ctrl + D is character 4 from the ASCII table, not a signal
*/
static struct termios 	new_termios;
static struct termios 	old_termios;
sigset_t				set;

void	set_terminal(void)
{
	tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	restore_terminal()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	sigemptyset(&set);
}

/*	handler for SIGINT signal */
void	handle_sigint(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*	set up of SIGINT sigaction, including set */
void	setup_sigint(void)
{
	struct sigaction		sa;

	set_terminal();
	sa.sa_sigaction = &handle_sigint;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaction(SIGINT, &sa, NULL);
}
