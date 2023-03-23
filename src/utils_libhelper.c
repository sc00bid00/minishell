/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libhelper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/22 17:35:57 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_my_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	if (ft_strlen(s1) >= ft_strlen(s2))
	{
		while (i <= ft_strlen(s2) && s1 && s2 && (s1[i] || s2[i]))
		{
		if ((unsigned char) s1[i] - (unsigned char) s2[i] != 0)
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
		}
	}
	else if (ft_strlen(s1) < ft_strlen(s2))
	{
		while (i <= ft_strlen(s1) && s1 && s2 && (s1[i] || s2[i]))
		{
		if ((unsigned char) s1[i] - (unsigned char) s2[i] != 0)
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
		}
	}
	return (0);
}
