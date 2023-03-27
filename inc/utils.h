/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:15:45 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 16:53:47 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ERROR_1 "No such file or directory"
# define ERROR_2 "numeric argument required"
# define ERROR_3 "too many arguments"
# define ERROR_4 "not a valid identifier"
# define ERROR_5 "environment not set"
# define ERROR_6 ": command not found"
# define ERROR_7 ": No such file or directory"
# define ERROR_8 ": Permission denied"
# define ERROR_9 "minishell: syntax error near unexpected token `"

t_env	*ms_lstlast(t_env *lst);
t_env	*ms_lstadd_back(t_env *env, t_env *temp);
int		ms_lstsize(t_env *lst);
char	*ms_multijoin(char const *s1, char c, char const *s2);
void	ft_ms_lstclear(t_env *lst);
void	ft_ms_lstdelone(t_env *env);
void	ft_error(char *s1, char *s2, char *mes);
void	ft_clean_env(t_env **env);
int		ft_my_strcmp(const char *s1, const char *s2);
void	ms_mycleanup(t_cmd *cmd, t_env **env);
void	ft_cleanenv(t_env **env);

#endif
