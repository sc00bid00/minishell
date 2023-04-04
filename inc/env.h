/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:52:24 by kczichow          #+#    #+#             */
/*   Updated: 2023/04/04 14:35:59 by kczichow         ###   ########.fr       */
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
char	**ft_arrenv(t_env *env);
char	*get_var_name(char *var);
char	*get_var_content(char *var);
t_env	*new_var(char *var);
t_env	*copy_envp_to_env(char **envp);

/* env_update */
t_env	*ret_prev_var(t_env **env, char *str);
t_env	*ret_var(t_env **env, char *str);
char	*upd_var(t_env **env, char *var, char *new_val);
t_env	*del_var(t_env **env, char *var);
void	increment_shlvl(t_env **env);

#endif
