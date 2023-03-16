/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:07:47 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/16 18:41:19 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* print lst->content to stdout */
void	tmp_prtlst(t_token *tkn)
{
	t_list	*tmp;

	ft_putendl_fd("*****\ntemp output for debugginig purpose", 2);
	ft_putstr_fd("*****\ninput string", 2);
	ft_putstr_fd(tkn->str, 2);
	ft_putendl_fd("\n=== output start ===", 2);
	tmp = tkn->lst;
	while (tmp)
	{
		ft_putendl_fd(tmp->content, 2);
		tmp = tmp->next;
	}
	ft_putstr_fd("=== output end ===\nchain with", 2);
	ft_putnbr_fd(tkn->count, 2);
	ft_putendl_fd(" nodes\n*****", 2);
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

void	tmp_helpprtcmd(int i, t_cmd **tmp)
{
	int	j;

	j = 0;
	while (tmp[i]->arr && tmp[i]->arr[j])
	{
		ft_putendl_fd(tmp[i]->arr[j], 2);
		j++;
	}
	if (tmp[i] && tmp[i]->arr)
		ft_putendl_fd(tmp[i]->arr[j], 2);
	write(1, "\n", 1);
	i++;
}

void	tmp_prtcmd(t_scmd *scmd)
{
	t_cmd	**tmp;
	int		i;

	tmp = scmd->cmd;
	i = 0;
	while (tmp && tmp[i])
	{
		ft_putnbr_fd(tmp[i]->stat, 2);
		ft_putstr_fd("\nInfile\t", 2);
		ft_putendl_fd(tmp[i]->in_name, 2);
		ft_putstr_fd("fd_in\t", 2);
		ft_putnbr_fd(tmp[i]->fd_in, 2);
		ft_putstr_fd("\nOutfile\t", 2);
		ft_putendl_fd(tmp[i]->out_name, 2);
		ft_putstr_fd("fd_out\t", 2);
		ft_putnbr_fd(tmp[i]->fd_out, 2);
		ft_putstr_fd("\nrule\t", 2);
		ft_putnbr_fd(tmp[i]->rule, 2);
		ft_putstr_fd("\nPath\t", 2);
		ft_putendl_fd(tmp[i]->path, 2);
		tmp_helpprtcmd(i, tmp);
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
