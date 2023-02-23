/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:52:24 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/23 14:29:15 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// # include "minishell.h"

typedef struct s_env
{
	char			*var_name;
	char			*var_content;
	struct s_env	*next;
}			t_env;

t_env	*copy_envp_to_env(char **envp);
char	**create_env_array(t_env *env);

#endif