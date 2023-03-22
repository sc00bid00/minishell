/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:52:24 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 10:02:45 by lsordo           ###   ########.fr       */
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

/* env_build */
char	*get_var_name(char *var);
char	*get_var_content(char *var);
t_env	*new_var(char *var, bool export);
t_env	*copy_envp_to_env(char **envp);

/* env_transform */
void	print_env_array(char **env_array);
char	**create_env_array(t_env *env);

/* env_update */
t_env	*ret_var(t_env *env, char *str);
char	*upd_var(t_env *env, char *var, char *new_val);
int		del_var(t_env *env, char *var);
void	del_first_var(t_env **env);

char	**ft_arrenv(t_env *env);

#endif
