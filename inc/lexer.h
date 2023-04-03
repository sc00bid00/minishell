/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:53:45 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/03 19:37:17 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define SINGLE_Q 0b000000001
# define DOUBLE_Q 0b000000010
# define SOME_Q 0b000000011
# define SPCE 0b000000100
# define RIN 0b000001000
# define ROUT 0b000010000
# define PIPE 0b000100000
# define DOLLAR 0b001000000
# define TILDE 0b010000000
# define CHAR 0b100000000

typedef struct s_token
{
	char	*str;
	t_list	*lst;
	int		prev;
	int		curr;
	int		nosub;
	int		c_sta;
	int		count;
	t_env	*env;
}			t_token;

t_token	*ft_lex(char *str, t_env *env);
void	ft_lex_uti(t_token *tkn);
void	ft_cleantkn(t_token *tkn);
void	ft_cleanlst(t_list *lst);
t_token	*ft_init_tkn(char *str, t_env *env);
t_token	*ft_redsyntax(t_token *tkn);
int		ft_istoken(void *content);
int		ft_flag(char c);
void	ft_expdollar(t_token *tkn);
t_list	*ft_moddollar(t_list *lst, t_token *tkn);
char	*ft_dollarsubst(char *str, t_token *tkn);
void	ft_spoillist(t_token *tkn);
void	ft_spoillist_util(char *tmps, t_list **copy);
char	*ft_lsttostr(t_list *lst);
void	ft_exptilde(t_token *tkn, int z);
int		ft_allspaces(char *str);
char	*ft_otherprefix(char *str, t_token *tkn);
char	*ft_putback(char *str, char *set1, char *set2);
void	ft_initredsyntax(int *flag, t_token *tkn, t_list **tmp, int (*i)[2]);
void	ft_helplsttostr(t_list *tmplst, int *i);
void	tmp_prtlst(t_token *tkn);
void	tmp_prtlst2(t_list *lst);
t_list *ft_strtolst(char *str);

#endif
