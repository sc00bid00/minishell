/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_to_heap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:56:46 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/16 15:07:17 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	temp_print_envs(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

char	**copy_env_to_heap(char **envp)
{
	char	**envp_copy;
	int		envp_len;
	int		i;
	int		len;

	envp_len = 0;
	i = 0;
	while (envp[envp_len])
		envp_len++;
	envp_copy = ft_calloc (sizeof(char **), envp_len + 1);
	if (!envp_copy)
		return (NULL);
	while (i < envp_len)
	{
		len = ft_strlen(envp[i]);
		envp_copy[i] = ft_calloc(sizeof (char *), (len + 1));
		ft_strlcpy (envp_copy[i], envp[i], len + 1);
		i++;
	}
	envp_copy[envp_len] = NULL;
	return (envp_copy);
}
