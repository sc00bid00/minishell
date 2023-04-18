/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:49:05 by lsordo            #+#    #+#             */
/*   Updated: 2022/10/30 13:49:58 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*copy_dst;
	char	*copy_src;
	size_t	i;

	if (!src && !dst)
		return (NULL);
	copy_dst = (char *)dst;
	copy_src = (char *)src;
	i = 0;
	while (i < n)
	{
		copy_dst[i] = copy_src[i];
		i++;
	}
	return (dst);
}
