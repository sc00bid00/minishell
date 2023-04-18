/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:58:15 by lsordo            #+#    #+#             */
/*   Updated: 2022/12/16 10:10:45 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(size_t n, char c)
{
	static int	cout;
	char		digt;
	char		conv;

	conv = 'a';
	cout = 0;
	if (c == 'X')
		conv = 'A';
	if (n >= 16)
	{
		ft_puthex(n / 16, c);
		n %= 16;
	}
	if (n < 10)
		digt = n + '0';
	if (n >= 10 && n < 16)
		digt = n - 10 + conv;
	cout++;
	write (1, &digt, 1);
	return (cout);
}

static int	ft_putpx(char c, va_list ptr)
{
	size_t	n;

	if (c == 'p')
		n = va_arg(ptr, unsigned long);
	else
		n = va_arg(ptr, unsigned int);
	if (c == 'p')
		return (ft_putstr_fd("0x", 1), ft_puthex(n, c) + 2);
	return (ft_puthex(n, c));
}

static int	ft_putdiucs(char c, va_list ptr)
{
	char		*s;
	long int	n;

	if (c == 'd' || c == 'i')
	{
		n = (long int)va_arg(ptr, int);
		if (n < 0)
			return (ft_putnbr_fd_m(n, 1) + 1);
		return (ft_putnbr_fd_m(n, 1));
	}
	if (c == 'u')
		return (ft_putnbr_fd_m((long int)va_arg(ptr, unsigned int), 1));
	if (c == 'c')
		return (ft_putchar_fd(va_arg(ptr, int), 1), 1);
	if (c == 's')
	{
		s = va_arg(ptr, char *);
		if (s == NULL)
			return (ft_putstr_fd("(null)", 1), 6);
		return (ft_putstr_fd(s, 1), (int)ft_strlen(s));
	}
	return (0);
}

static int	ft_triage(char *frmt, va_list ptr)
{
	char	c;

	c = *(frmt + 1);
	if (c == 'd' || c == 'i' || c == 'u' || c == 'c' || c == 's')
		return (ft_putdiucs(c, ptr));
	if (c == 'p' || c == 'x' || c == 'X')
		return (ft_putpx(c, ptr));
	if (c == '%')
		return (ft_putchar_fd('%', 1), 1);
	return (0);
}

int	ft_printf(const char *frmt, ...)
{
	va_list		ptr;
	int			i;
	int			ret;

	va_start(ptr, frmt);
	ret = 0;
	i = 0;
	while (frmt[i])
	{
		if (frmt[i] == '%')
		{
			ret += ft_triage((char *)&frmt[i], ptr);
			i += 2;
		}
		else
		{
			write (1, &frmt[i], 1);
			i++;
			ret++;
		}
	}
	va_end(ptr);
	return (ret);
}
