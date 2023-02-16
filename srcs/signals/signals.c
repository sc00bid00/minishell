/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 08:50:56 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/16 14:21:55 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

// static struct termios old_termios;
/*	SIGINT = Ctrl + C;
*	SIGQUIT = Ctrl \
*	Ctrl + D is character 4 from the ASCII table
*/

// static struct termios old_termios;

// void restore_terminal() {
//     tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
// }

// void handle_signal(int sig) {
//     restore_terminal();
//     printf("Signal %d received\n", sig);
//     // Handle the signal here
//     exit(0);
// }

// int main() {
//     // Set up the signal handler for SIGINT
//     struct sigaction sa;
//     sa.sa_handler = handle_signal;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sigaction(SIGINT, &sa, NULL);

//     // Save the current terminal settings and turn off ECHO
//     struct termios new_termios;
//     tcgetattr(STDIN_FILENO, &old_termios);
//     new_termios = old_termios;
//     new_termios.c_lflag &= ~ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

//     // Wait for input
//     char buf[256];
//     printf("Enter input: ");
//     fgets(buf, sizeof(buf), stdin);
//     printf("Input: %s\n", buf);

//     // Restore the terminal settings before exiting
//     restore_terminal();

//     return 0;

// }
void restore_terminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	sigemptyset(&set);
}

void	handle_sigint(int signal, siginfo_t *info, void *context)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void setup_sigint()
{
	sa.sa_sigaction = &handle_sigint;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaction(SIGINT, &sa, NULL);
}