/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:49:07 by lsordo            #+#    #+#             */
/*   Updated: 2022/10/18 16:27:55 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*c_s;
	size_t	i;

	c_s = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c_s[i] == (unsigned char)c)
			return (c_s + i);
		i++;
	}
	return (NULL);
}
