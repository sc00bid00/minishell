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

/* compares two strings */
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

/* joins two strings and a char */
char	*ms_multijoin(char const *s1, char c, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || ! s2)
		return (NULL);
	len = ft_strlen(s1) + 1 + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), &c, 1);
	ft_memcpy(str + ft_strlen(s1) + 1, s2, ft_strlen(s2));
	*(str + ft_strlen(s1) + 1 + ft_strlen(s2)) = '\0';
	return (str);
}
