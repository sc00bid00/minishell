/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/17 12:56:46 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

void	ft_getwords(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;

	while (tmp)
	{
		if (((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content)
		{
			ft_lstadd_back(&arr[cmd->count], ft_strdup(tmp->content));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

void	ft_getappend(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;
	int		flag;

	arr = cmd->arr;
	tmp = tkn->lst;
	flag = 0;
	while (tmp)
	{
		if (((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strcmp(tmp->content, ">>", 1) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_strdup(tmp->content));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

void	ft_getredout(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;
	int		flag;

	arr = cmd->arr;
	tmp = tkn->lst;
	flag = 0;
	while (tmp)
	{
		if (((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strcmp(tmp->content, ">", 1) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_strdup(tmp->content));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

void	ft_getredin(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;
	int		flag;

	arr = cmd->arr;
	tmp = tkn->lst;
	flag = 0;
	while (tmp)
	{
		if (((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strcmp(tmp->content, "<", 1) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_strdup(tmp->content));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

void	ft_gethdoc(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;
	int		flag;

	arr = cmd->arr;
	tmp = tkn->lst;
	flag = 0;
	while (tmp)
	{
		if (((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strcmp(tmp->content, "<<", 2) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_strdup(tmp->content));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

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
