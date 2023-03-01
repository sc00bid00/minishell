/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:15:45 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/01 13:38:41 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*	utils_list */
t_env	*ms_lstlast(t_env *lst);
t_env	*ms_lstadd_back(t_env *env, t_env *temp);
int		ms_lstsize(t_env *lst);
char	*ms_multijoin(char const *s1, char c, char const *s2);
void	ft_ms_lstclear(t_env *lst);
void	ft_ms_lstdelone(t_env *env);

/* utils_error */
void	ft_error(char *s1, char *s2, int i);

// typedef enum
// {
// 	ERROR_1 = 0,
// 	ERROR_2 = 1,
// 	ERROR_3 = 2,
// 	NUM_ERRORS
// } errcode;

// typedef struct
// {
// 	const char* message;
// }ErrorMessages[NUM_ERRORS];

// static const ErrorMessages error_messages =
// {
// 	[ERROR_1] = {"invalid argument"},
// 	[ERROR_2] = {"invalid argument"},
// 	[ERROR_3] = {"invalid argument"},	
// };


#endif