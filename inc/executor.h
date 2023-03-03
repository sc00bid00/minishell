/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:49 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/03 11:21:58 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		ft_pipe(t_scmd *scmd);
int		ft_helpexecutor(t_scmd *scmd);
int		ft_pipein(t_scmd *scmd);
int		ft_firstcmd(t_scmd *scmd);
void	tmp_prtlst2(t_list *lst);
#endif
