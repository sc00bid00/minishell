/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:56:37 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 14:39:49 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

char	*read_line(void);
int		get_input(char **envp, t_env **env);
int		test_get_input(char **envp, t_env **env, char *input);

#endif
