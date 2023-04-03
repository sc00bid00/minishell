/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:49 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/03 14:15:43 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	ft_eerr(void *fst_msg, void *snd_msg, void *trd_msg);
void	ft_exec(t_scmd *scmd);
void	ft_exec_fork(t_scmd *scmd);
void	ft_child(t_scmd *scmd);
void	ft_parent(t_scmd *scmd);
void	ft_noredirect(t_scmd *scmd);
void	ft_execute(t_scmd *scmd);
void	ft_fileissues(t_scmd *scmd);
void	ft_cmdissues(t_scmd *scmd);
void	ft_redirect(t_scmd *scmd);

#endif
