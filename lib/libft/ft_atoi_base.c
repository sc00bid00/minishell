/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:17:34 by lsordo            #+#    #+#             */
/*   Updated: 2023/01/05 15:45:08 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_mklc(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] += 32;
		}
		i++;
	}
	return (s);
}

uint32_t	ft_cnum(char *s, uint32_t str_base)
{
	uint32_t	rslt;
	char		*base;
	uint32_t	n;
	int			i;

	base = "0123456789abcdef";
	rslt = 0;
	i = 0;
	while (s[i])
	{
		n = 0;
		while (base[n])
		{
			if (s[i] == base[n])
				break ;
			n++;
		}
		rslt = rslt * str_base + n;
		i++;
	}
	return (rslt);
}

uint32_t	ft_atoi_base(const char *str, uint32_t str_base)
{
	uint32_t	sign;
	uint32_t	rslt;
	int			i;
	char		*s;

	if (!ft_strncmp(str, "0X", 2) || !ft_strncmp(str, "0x", 2))
		str = str + 2;
	s = ft_mklc((char *)str);
	sign = 1;
	i = 0;
	while (str[i] <= 32)
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i ++;
	}
	else if (s[i] == '+')
		i++;
	rslt = ft_cnum(&s[i], str_base);
	rslt *= sign;
	return (rslt);
}
