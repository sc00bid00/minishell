/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:06:49 by lsordo            #+#    #+#             */
/*   Updated: 2022/11/03 12:26:08 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static	int	ft_cmp(const char *hs, const char *nd, size_t len)
{
	size_t	i;

	i = 0;
	while (*nd && i < len)
	{
		if (*hs != *nd)
			return (0);
		hs++;
		nd++;
		i++;
	}
	if (*nd)
		return (0);
	return (1);
}

char	*ft_strnstr(const char *hs, const char *nd, size_t len)
{
	size_t	i;

	if (hs == NULL && len == 0)
		return (NULL);
	if (!*nd)
		return ((char *)hs);
	i = 0;
	while (*hs && i < len)
	{
		if (*hs == *nd && ft_cmp(hs, nd, len) && i <= len - ft_strlen(nd))
			return ((char *)hs);
		hs++;
		i++;
	}
	return (NULL);
}
