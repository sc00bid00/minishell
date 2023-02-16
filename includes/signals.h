/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:39:24 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/16 16:26:20 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include "minishell.h"

struct sigaction		sa;
struct sigaction		sb;
struct termios 			new_termios;
static struct termios 	old_termios;
sigset_t				set;

void	setup_signals(bool interactive);
void	signal_handler(int signal);
void	restore_terminal();
void	setup_sigint();
void	handle_sigint(int signal, siginfo_t *info, void *context);

#endif