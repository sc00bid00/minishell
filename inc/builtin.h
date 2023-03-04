/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:16:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/04 10:23:46 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	builtin_pwd(void);
int	builtin_cd(int argc, char **argv, t_env *env);
int	builtin_env(int argc, char **argv, t_env *env);
int print_env(t_env *env, bool export);
int	builtin_echo(int argc, char **argv, t_env *env);
int	builtin_unset(int arg, char **argv, t_env *env);
int	builtin_export(int argc, char **argv, t_env *env);
int builtin_exit(int argc, char **argv, t_env *env);

#endif
