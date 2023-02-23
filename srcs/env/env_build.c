/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:47:21 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/23 14:28:37 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;

	if (!s || len == 0)
		return (NULL);
	if (start > strlen(s))
		len = 0;
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && *(s + start + i))
	{
		ptr[i] = (char)s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*	print environment list */
void	print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s", env->var_name);
		printf("=");
		printf("%s\n", env->var_content);
		env = env->next;
	}
}

/*	extract and return variable name from envp */
char	*get_var_name(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	var_name = ms_substr(var, 0, i);
	return (var_name);
}

/*	extract and return variable content from envp*/
char	*get_var_content(char *var)
{
	unsigned int		i;
	size_t				len;
	char				*var_content;

	i = 0;
	len = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != '=')
		return (NULL);
	else
	{
		while (var[len])
			len++;
		var_content = ms_substr(var, i + 1, len);
	}
	return (var_content);
}

/*	create new node, assign var name and var content */
t_env	*new_var(char *var)
{
	t_env	*temp;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return (NULL);
	else
	{
		temp->var_name = get_var_name(var);
		temp->var_content = get_var_content(var);
		temp->next = NULL;
	}
	return (temp);
}

/*	copy strings from envp array to list, each str to a new node */
t_env	*copy_envp_to_env(char **envp)
{
	t_env	*env;
	t_env	*temp;
	int		i;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{	
		temp = new_var(envp[i]);
		if (!temp)
			return (env);
		env = ms_lstadd_back(env, temp);
		i++;
	}
	// print_env(env);
	return (env);
}
