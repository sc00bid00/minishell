/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:39:24 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 17:13:54 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	set_terminal(void);
void	handle_sigint(int signal, siginfo_t *info, void *context);
void	setup_sigint(void);
void	restore_signal(void);

#endif
