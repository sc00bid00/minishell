/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:16:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/04 08:30:42 by lsordo           ###   ########.fr       */
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

// echo
char				**ft_lsttoarr(t_list *lst);
void				ft_echoadjarr(t_list *lst, char ***arr);
int					ft_isdquote(char *str);
int					ft_isredtoken(char *str);
void				ft_rmred(t_list **lst);
void				ft_spoilecho_util(t_list *tmp);
void				ft_spoilecho(t_list **lst);
int					ft_isvoption(char *str);
t_list				*ft_strtolstecho(char *str);
void				ft_remspcnul(t_list **lst);
void				ft_expdollarecho(t_token *tkn);
void				ft_goecho(t_token *tkn);
void				ft_lex_util(t_token *tkn);
t_token				*ft_lexecho(char *str, t_env *env);
void				ft_splitlist_util(t_list **copylst, t_list *lst, int j);
void				ft_splitlist(t_cmd *cmd, t_env **env);
int					check_n(char **arr, t_cmd *cmd);
void				check_redir(t_cmd *cmd);

#endif
