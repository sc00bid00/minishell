/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:41:37 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/27 16:20:18 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define FILE_KO 0b000101
# define IN_KO 0b000001
# define OUT_KO 0b000100
# define RED_OK 0b001010
# define IN_OK 0b000010
# define OUT_OK 0b001000
# define CMD_KO 0b010000
# define EX_OK 0b100000

/* cmd to be used in execution */
typedef struct s_cmd
{
	char			*in_name;
	char			*out_name;
	int				fd_in;
	int				fd_out;
	char			*path;
	char			**arr;
	int				argc;
	int				err_flag;
	int				hd_flag;
	int				rule;
	int				stat;
	int				builtin;
	struct s_scmd	*scmd;
}			t_cmd;

/* simple cmd used in parser and prexec */
typedef struct s_scmd
{
	int		count;
	int		n_scmd;
	int		fd[2];
	int		store[2];
	int		id;
	char	**envp;
	int		wstatus;
	int		flag;
	t_list	*hdocs;
	t_list	**arr;
	t_cmd	**cmd;
	t_env	*env;
}			t_scmd;

t_scmd	*ft_parse(t_token *tkn, char **arr, t_env *env);
t_scmd	*ft_init_scmd(t_token *tkn, char **arr, t_env *env);
int		ft_init_cmd(t_scmd *scmd);
void	ft_gethdoc(t_token *tkn, t_scmd *cmd);
void	ft_getred(t_token *tkn, t_scmd *cmd);
void	ft_getwords(t_token *tkn, t_scmd *cmd);
int		ft_prexec(t_scmd *scmd);
void	ft_helppaths(t_cmd *cmd, char **arr, int j);
void	ft_isin(t_list *lst, t_scmd *scmd);
void	ft_isout(t_list *lst, int *count, t_scmd *scmd);
int		ft_isword(t_list **lst, int *count, t_scmd *scmd);
void	ft_helpisheredoc(t_scmd	*scmd, t_cmd **tmp);
void	ft_cleancmd(t_scmd *scmd);
void	ft_cleanscmd(t_scmd *cmd);
void	tmp_prtarrlst(t_scmd *cmd);
void	tmp_prtcmd(t_scmd *scmd);

#endif
