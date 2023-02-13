/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:41:49 by lsordo            #+#    #+#             */
/*   Updated: 2022/11/03 14:28:26 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	ch;

	ch = (char)c;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len] == ch)
			return ((char *)&s[len]);
		len--;
	}
	if (s[0] == ch)
		return ((char *)&s[len]);
	return (NULL);
}
