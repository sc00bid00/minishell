/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:47:21 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/27 11:08:11 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_arrenv(t_env *env)
{
	t_env	*tmp;
	int		size;
	char	**arr;
	int		i;

	size = ms_lstsize(env);
	arr = ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		exit(EXIT_FAILURE);
	tmp = env;
	i = 0;
	while (tmp)
	{
		arr[i] = ms_multijoin(tmp->var_name, '=', tmp->var_content);
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

/*	extract and return variable name from envp */
char	*get_var_name(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	var_name = ft_substr(var, 0, i);
	return (var_name);
}

/*	extract and return variable content from envp*/
char	*get_var_content(char *var)
{
	size_t		i;
	size_t		len;
	char		*var_content;

	i = 0;
	len = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (i == ft_strlen(var))
		return (NULL);
	while (var[len])
		len++;
	var_content = ft_substr(var, i + 1, len);
	return (var_content);
}

/*	create new node, assign var name and var content */
t_env	*new_var(char *var)
{
	t_env	*temp;

	temp = ft_calloc(sizeof(t_env), 1);
	if (!temp)
		return (NULL);
	temp->var_name = get_var_name(var);
	if (!temp->var_name)
	{
		free (temp);
		return (NULL);
	}
	temp->var_content = get_var_content(var);
	temp->next = NULL;
	return (temp);
}

t_env	*copy_envp_to_env(char **envp)
{
	t_env	*env;
	t_env	*temp;
	int		i;

	i = 0;
	env = NULL;
	print_env_array(envp);
	while (envp && envp[i])
	{
		temp = new_var(envp[i]);
		if (!temp)
			return (env);
		env = ms_lstadd_back(env, temp);
		i++;
	}
	return (env);
}
