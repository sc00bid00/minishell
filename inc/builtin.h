/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:16:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 13:56:28 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <minishell.h>

int	builtin_pwd(t_cmd *cmd, t_env *env);
int	builtin_cd(t_cmd *cmd, t_env *env);
int	builtin_env(t_cmd *cmd, t_env *env);
int	builtin_echo(t_cmd *cmd, t_env *env);
int	builtin_unset(t_cmd *cmd, t_env *env);
int	builtin_export(t_cmd *cmd, t_env *env);
int builtin_exit(t_cmd *cmd, t_env *env);
int print_env(t_env *env, bool ex);

#endif
