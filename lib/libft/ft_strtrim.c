/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:03:22 by lsordo            #+#    #+#             */
/*   Updated: 2023/01/04 11:31:26 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static	char	*ft_allncpy(char const *s1, size_t start, size_t len)
{
	char	*ptr;

	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1 + start, len);
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_allncpy(s1, 0, ft_strlen(s1)));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[end]) && end > start)
		end--;
	if (start == ft_strlen(s1))
		return (ft_allncpy(s1, 0, 0));
	len = end - start + 1;
	return (ft_allncpy(s1, start, len));
}
