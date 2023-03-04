/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:49 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/04 12:11:35 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		ft_pipe(t_scmd *scmd);
int		ft_helpexecutor(t_scmd *scmd);
int		ft_pipein(t_scmd *scmd);
int		ft_firstcmd(t_scmd *scmd);
int		ft_builtin(t_scmd *scmd);
int		ft_helppipe(t_scmd *scmd);
void	tmp_prtlst2(t_list *lst);
int		ft_child(t_scmd	*scmd);
#endif
