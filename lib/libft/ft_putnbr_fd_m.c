/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:06:38 by lsordo            #+#    #+#             */
/*   Updated: 2022/12/16 10:15:54 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_putnbr_fd_m(long int n, int fd)
{
	static int		cout;

	cout = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd_m(n / 10, fd);
		n %= 10;
	}
	ft_putchar_fd(n + '0', fd);
	cout ++;
	return (cout);
}
