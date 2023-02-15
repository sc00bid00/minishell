/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:41:37 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/15 17:05:03 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <unistd.h>
# include <stdlib.h>
# include <libft.h>
# include <lexer.h>

typedef struct s_scmd
{
	int		count;
	char	**scmd;
}			t_scmd;

#endif
