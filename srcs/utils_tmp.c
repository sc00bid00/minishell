/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:07:47 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/28 16:46:24 by lsordo           ###   ########.fr       */
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
		ft_printf("%s \n", tmp->content);
		tmp = tmp->next;
	}
	ft_printf("=== output end ===\nchain with %d nodes\n*****\n", tkn->count);
}

/* print *lst->content to stdout*/
void	tmp_prtarrlst(t_scmd *cmd)
{
	t_list	*tmp;
	int		i;

	ft_printf("=== output start ===\n");
	i = 0;
	while (cmd->arr[i])
	{
		tmp = cmd->arr[i];
		while (tmp)
		{
			ft_printf("%s, ", tmp->content);
			tmp = tmp->next;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("=== output end ===\n");
}

void	tmp_prtcmd(t_scmd *scmd)
{
	t_cmd	**tmp;
	int		i;
	int		j;

	tmp = scmd->cmd;
	i = 0;
	while (tmp && tmp[i])
	{
		ft_printf("Infile  %s\tfd %d\nOutfile %s\tfd %d\n", tmp[i]->in_name, \
			tmp[i]->fd_in, tmp[i]->out_name, tmp[i]->fd_out);
		j = 0;
		while (tmp[i]->arr && tmp[i]->arr[j])
		{
			ft_printf("%d.%d %s\n", i, j, tmp[i]->arr[j]);
			j++;
		}
		i++;
	}
}
