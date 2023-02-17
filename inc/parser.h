/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:41:37 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/17 14:44:29 by lsordo           ###   ########.fr       */
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
	int		n_scmd;
	int		hdoc;
	t_list	**arr;
}			t_scmd;

void	tmp_prtarrlst(t_scmd *cmd);

#endif
