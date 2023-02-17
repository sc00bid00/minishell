/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/17 10:17:00 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

int	ft_ctscmd(t_scmd *scmd, t_token *tkn)
{
	t_list	*tmp;

	tmp = tkn->lst;
	while (tmp)
	{
		if (((char *)(tmp->content))[0] == '|')
			scmd->n_scmd++;
		tmp = tmp->next;
	}
	scmd->n_scmd++;
	return (scmd->n_scmd);
}

t_scmd	*ft_init_scmd(t_token *tkn)
{
	t_scmd	*scmd;

	scmd = malloc(sizeof(t_scmd));
	if (!scmd)
		return (NULL);
	scmd->n_scmd = 0;
	scmd->n_scmd = ft_ctscmd(tkn);
	scmd->arr = NULL;
	scmd->arr = ft_alloc(scmd->n_scmd + 1, sizeof(t_list *));
	if (!scmd->arr)
	{
		ft_cleanup(tkn);
		return (NULL);
	}
	scmd->count = 0;
	return (scmd);
}

void	ft_gethdoc(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	int		flag;

	flag = 0;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && !cmd->count \
			&& (!ft_strncmp(tmp->content, "<<", 2) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&cmd->arr[cmd->count], tmp->content);
		}
		tmp = tmp->next;
	}
}

t_scmd	*ft_parse(t_token *tkn)
{
	t_scmd	*scmd;
	t_list	*tmp;

	scmd = NULL;
	scmd = ft_init_scmd(tkn);

	return (scmd);
}

int	main(void)
{
	char	*str;
	t_token	*tkn;
	t_scmd	*scmd;

	str = "< infile.txt cat -e| grep $USER >>out<< stop1 << stop2";
	tkn = ft_lex(str);
	scmd = ft_parse(tkn);
	ft_printf("counted %d simple command(s)\n", scmd->n_scmd);

	// tmp_prtlst(tkn);
	ft_cleanup(tkn);
	return (0);
}
