/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 08:50:56 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 17:13:08 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*	signals to be managed within minishell:		 				*/
/*	SIGINT = Ctrl + C; 											*/
/*	SIGQUIT = Ctrl \; 											*/
/*	Ctrl + D (not a signal, character 4 from the ASCII table) 	*/

/* function disables echoing of control characters on the terminal */
void	set_terminal(void)
{
	static struct termios	new_termios;
	static struct termios	old_termios;

	tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
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
		g_exitstatus = 1;
	}
}

/*	set up of SIGINT sigaction for interactive mode */
void	setup_sigint(void)
{
	struct sigaction		sa;
	sigset_t				set;

	ft_memset(&sa, 0, sizeof(sa));
	set_terminal();
	sa.sa_sigaction = &handle_sigint;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaction(SIGINT, &sa, NULL);
}

/*	restore signals to dfault behavior in non-interactive mode (child process)*/
void	restore_signal(void)
{
	struct sigaction	default_action;

	ft_memset(&default_action, 0, sizeof(default_action));
	default_action.sa_handler = SIG_DFL;
	sigemptyset(&default_action.sa_mask);
	default_action.sa_flags = 0;
	sigaction(SIGQUIT, &default_action, NULL);
	sigaction(SIGINT, &default_action, NULL);
}
