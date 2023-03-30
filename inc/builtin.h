/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:16:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/29 21:56:35 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <minishell.h>

int (*ft_builtin(t_scmd	*scmd))(t_cmd *cmd, t_env **env);
int					builtin_pwd(t_cmd *cmd, t_env **env);
int					builtin_cd(t_cmd *cmd, t_env **env);
int					builtin_env(t_cmd *cmd, t_env **env);
int					builtin_echo(t_cmd *cmd, t_env **env);
int					builtin_unset(t_cmd *cmd, t_env **env);
int					builtin_export(t_cmd *cmd, t_env **env);
int					builtin_exit(t_cmd *cmd, t_env **env);
unsigned long long	ft_atoi_long_long(char *str);
int					print_env(t_env **env);

#endif
