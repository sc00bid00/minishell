/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:53:45 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/14 16:24:55 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

typedef struct s_token
{
	char	*str;
	t_list	*lst;
	int		prev;
	int		curr;
	int		p_sta;
	int		c_sta;
	int		count;
}			t_token;

#endif
