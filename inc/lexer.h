/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:53:45 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/24 08:23:01 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	char	*str;
	t_list	*lst;
	int		prev;
	int		curr;
	int		p_sta;
	int		c_sta;
	int		count;
	t_env	*env;
}			t_token;

t_token	*ft_lex(char *str, t_env *env);
void	ft_cleantkn(t_token *tkn);
void	ft_cleanlst(t_list *lst);
t_token	*ft_init_tkn(char *str, t_env *env);
void	ft_helplexer(t_token *tkn);
void	ft_save(t_token *tkn);
t_token	*ft_redsyntax(t_token *tkn);
void	ft_explode(t_list **lst, char *str);
void	ft_substitute(t_list **lst, t_env *var);
void	ft_reassemble(t_list *lst, t_list **node);
void	ft_remquotes(t_token *tkn);
int		ft_istoken(void *content);
int		ft_iscapital(int c);
void	tmp_prtlst(t_token *tkn);
void	tmp_prtlst2(t_list *lst);

#endif
