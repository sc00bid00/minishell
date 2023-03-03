/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:39:24 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/03 13:35:24 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	setup_signals(bool interactive);
void	signal_handler(int signal);
void	restore_terminal();
void	setup_sigint();
void	handle_sigint(int signal, siginfo_t *info, void *context);

#endif
