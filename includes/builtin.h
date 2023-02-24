/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:16:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/24 13:10:54 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int_fast64_t	builtin_pwd(void);
t_env	*builtin_cd(int argc, char **argv, t_env *env);


#endif