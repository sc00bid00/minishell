/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:50:53 by lsordo            #+#    #+#             */
/*   Updated: 2022/10/31 09:29:15 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static	int	ft_size(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static	char	*ft_builds(int n, int sign)
{
	int		size;
	char	*s;

	size = ft_size(n);
	s = malloc((sign + size + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[size + sign] = '\0';
	while (size > 0)
	{
		s[--size + sign] = n % 10 + '0';
		n /= 10;
	}
	if (sign > 0)
		s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	int	sign;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	return (ft_builds(n, sign));
}
