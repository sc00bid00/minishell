/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:53:45 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/03 11:20:48 by lsordo           ###   ########.fr       */
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
}			t_token;

t_token	*ft_lex(char *str);
void	ft_cleantkn(t_token *tkn);
void	ft_cleanlst(t_list *lst);
t_token	*ft_init_tkn(char *str);
void	ft_helplexer(t_token *tkn);
void	ft_save(t_token *tkn);
t_token	*ft_unextkn(t_token *tkn);
void	tmp_prtlst(t_token *tkn);

#endif