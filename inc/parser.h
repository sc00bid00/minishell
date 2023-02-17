/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:41:37 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/17 16:11:43 by lsordo           ###   ########.fr       */
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

t_scmd	*ft_parse(t_token *tkn);
t_scmd	*ft_init_scmd(t_token *tkn);
void	ft_gethdoc(t_token *tkn, t_scmd *cmd);
void	ft_getredin(t_token *tkn, t_scmd *cmd);
void	ft_getredout(t_token *tkn, t_scmd *cmd);
void	ft_getappend(t_token *tkn, t_scmd *cmd);
void	ft_getwords(t_token *tkn, t_scmd *cmd);
void	ft_cleanscmd(t_scmd *cmd);
void	tmp_prtarrlst(t_scmd *cmd);

#endif
