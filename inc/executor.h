/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:49 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/11 14:58:39 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	ft_eerr(t_cmd *cmd, int err, void *message, void *name);
void	ft_exec(t_scmd *scmd);

#endif
