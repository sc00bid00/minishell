/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:16:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/17 11:55:14 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <minishell.h>

int		(*ft_builtin(t_scmd *scmd))(t_cmd *, t_env *);
int		builtin_pwd(t_cmd *cmd, t_env *env);
int		builtin_cd(t_cmd *cmd, t_env *env);
int		builtin_env(t_cmd *cmd, t_env *env);
int		builtin_echo(t_cmd *cmd, t_env *env);
int		builtin_unset(t_cmd *cmd, t_env *env);
int		builtin_export(t_cmd *cmd, t_env *env);
char	*get_var_name_export(char *var);
int		builtin_exit(t_cmd *cmd, t_env *env);
unsigned long long	ft_atoi_long_long(char *str);
int		print_env(t_env *env, bool ex);

#endif
