/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_tmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:07:47 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/17 14:46:37 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

/* print lst->content to stdout */
void	tmp_prtlst(t_token *tkn)
{
	t_list	*tmp;

	ft_printf("*****\ntemp output for debugginig purpose\n");
	ft_printf("*****\ninput string \"%s\"\n=== output start ===\n", tkn->str);
	tmp = tkn->lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_printf("=== output end ===\nchain with %d nodes\n*****\n", tkn->count);
}

void	tmp_prtarrlst(t_scmd *cmd)
{
	t_list	*tmp;
	int		i;

	ft_printf("=== output start ===\n");
	i = 0;
	while (cmd->arr[i])
	{
		tmp = cmd->arr[i];
		ft_printf("simple command %d of %d\n", i + 1, cmd->n_scmd);
		while (tmp)
		{
			ft_printf("%s ", tmp->content);
			tmp = tmp->next;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("=== output end ===\n");
}
