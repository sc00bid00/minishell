/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:15:45 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/06 17:22:33 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ERROR_1 "message to be created\n"
# define ERROR_2 "message to be created\n"
# define ERROR_3 "message to be created\n"
# define ERROR_4 "not a valid identifier\n"

t_env	*ms_lstlast(t_env *lst);
t_env	*ms_lstadd_back(t_env *env, t_env *temp);
int		ms_lstsize(t_env *lst);
char	*ms_multijoin(char const *s1, char c, char const *s2);
void	ft_ms_lstclear(t_env *lst);
void	ft_ms_lstdelone(t_env *env);
void	ft_error(char *s1, char *s2, char *mes);

#endif
