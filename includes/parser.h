/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:41:37 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/27 14:53:14 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <libft.h>
# include <lexer.h>
# include <get_next_line.h>

typedef struct s_cmd
{
	char	*in_name;
	char	*out_name;
	int		fd_in;
	int		fd_out;
	char	*path;
	char	**arr;
	int		hd_flag;
}			t_cmd;

typedef struct s_scmd
{
	int		count;
	int		n_scmd;
	t_list	**arr;
	t_cmd	**cmd;
}			t_scmd;

t_scmd	*ft_parse(t_token *tkn);
t_scmd	*ft_init_scmd(t_token *tkn);
int		ft_init_cmd(t_scmd *scmd);
void	ft_gethdoc(t_token *tkn, t_scmd *cmd);
void	ft_getredin(t_token *tkn, t_scmd *cmd);
void	ft_getredout(t_token *tkn, t_scmd *cmd);
void	ft_getappend(t_token *tkn, t_scmd *cmd);
void	ft_getwords(t_token *tkn, t_scmd *cmd);
int		ft_prexec(t_scmd *scmd);
void	ft_isin(t_list *lst, int *count, t_scmd *scmd);
void	ft_isout(t_list *lst, int *count, t_scmd *scmd);
int		ft_isword(t_list *lst, int *count, t_scmd *scmd);
void	ft_cleanscmd(t_scmd *cmd);
void	tmp_prtarrlst(t_scmd *cmd);
void	tmp_prtcmd(t_scmd *scmd);

#endif
