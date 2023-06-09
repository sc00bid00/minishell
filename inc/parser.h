/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:41:37 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 18:50:26 by lsordo           ###   ########.fr       */
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
# define IS_DIR 0b1000000
# define SLASH 0b10000000

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
	int				optn;
	struct s_scmd	*scmd;
	char			*str;
	int				count;
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
	int		dir;
	t_list	*hdocs;
	t_list	**arr;
	t_cmd	**cmd;
	t_env	*env;
	char	*str;
}			t_scmd;

t_scmd	*ft_parse(t_token *tkn, char **arr, t_env *env);
t_scmd	*ft_init_scmd(t_token *tkn, char **arr, t_env *env);
int		ft_init_cmd(t_scmd *scmd);
void	ft_gethdoc(t_token *tkn, t_scmd *cmd);
void	ft_getred(t_token *tkn, t_scmd *cmd);
void	ft_getwords(t_token *tkn, t_scmd *cmd);
int		ft_prexec(t_scmd *scmd);
void	ft_helpprexec(t_cmd *cmd, t_scmd *scmd);
void	ft_helppaths(t_cmd *cmd, char **arr, int j);
int		ft_absrelpath(t_cmd *cmd);
void	ft_paths(t_scmd *scmd);
void	ft_isin(t_list *lst, t_scmd *scmd);
void	ft_isout(t_list *lst, int *count, t_scmd *scmd);
int		ft_isword(t_list **lst, int *count, t_scmd *scmd);
void	ft_helpisheredoc(t_scmd	*scmd, t_cmd **tmp);
void	ft_helpisheredoc_2(t_cmd *tmp);
void	ft_hdocdollar(char **str, t_scmd *scmd);
char	*ft_dollarsubst2(char *str, t_scmd *scmd);
void	ft_cleancmd(t_scmd *scmd);
void	ft_cleanscmd(t_scmd *cmd);
void	tmp_prtarrlst(t_scmd *cmd);
void	tmp_prtcmd(t_scmd *scmd);
void	tmp_prtarray(char **arr);

#endif
