/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:17:24 by lsordo            #+#    #+#             */
/*   Updated: 2022/11/02 20:56:30 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static	int	ft_overlap(char	*dst, char *src, size_t len)
{
	if (src < dst && src + len > dst)
		return (1);
	return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmpd;
	char	*tmps;

	if (src == dst || len == 0)
		return (dst);
	tmpd = (char *)dst;
	tmps = (char *)src;
	if (!ft_overlap(tmpd, tmps, len))
		ft_memcpy(tmpd, tmps, len);
	else
	{
		while (len > 0)
		{
			tmpd[len - 1] = tmps[len - 1];
			len--;
		}
	}
	return (dst);
}
