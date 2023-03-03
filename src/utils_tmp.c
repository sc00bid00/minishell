/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:07:47 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/03 13:40:22 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell.h>

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
		ft_printf("Infile  %s\nfd      %d\nOutfile %s\nfd      %d\n"\
			, tmp[i]->in_name, tmp[i]->fd_in, tmp[i]->out_name, tmp[i]->fd_out);
		ft_printf("rule    %d\npath    %s\n", tmp[i]->rule, tmp[i]->path);
		j = 0;
		while (tmp[i]->arr && tmp[i]->arr[j])
		{
			ft_printf("%d.%d     %s\n", i, j, tmp[i]->arr[j]);
			j++;
		}
		if (tmp[i] && tmp[i]->arr)
			ft_printf("%d.%d     %s\n", i, j, tmp[i]->arr[j]);
		write(1, "\n", 1);
		i++;
	}
}

void	tmp_prtlst2(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
