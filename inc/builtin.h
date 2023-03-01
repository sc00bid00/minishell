/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:16:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/01 09:58:02 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	builtin_pwd(void);
int	builtin_cd(int argc, char **argv, t_env *env);
int	builtin_env(int argc, char **argv, t_env *env);
int print_env(t_env *env);
int	builtin_echo(int argc, char **argv, t_env *env);
int	builtin_unset(int arg, char **argv, t_env *env);


#endif