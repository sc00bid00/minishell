/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:52:24 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/24 13:08:18 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*var_name;
	char			*var_content;
	struct s_env	*next;
}			t_env;

t_env	*copy_envp_to_env(char **envp);
char	**create_env_array(t_env *env);
void	print_env(t_env *env);
t_env	*update_variable(t_env *env, char *var, char *new_val);
char	*return_var_content(t_env *env, char *str);

#endif