/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:49 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/16 18:49:50 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	ft_eerr(void *fst_msg, void *snd_msg, void *trd_msg);
void	ft_exec(t_scmd *scmd);
void	ft_noredirect(t_scmd *scmd);
void	ft_execute(t_scmd *scmd);
void	ft_fileissues(t_scmd *scmd);
void	ft_cmdissues(t_scmd *scmd);
void	ft_redirect(t_scmd *scmd);

#endif
