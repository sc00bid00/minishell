/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/17 14:59:03 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

/* return words out of t_token.lst to t_scmd.t_list ** */
void	ft_getwords(t_token *tkn, t_scmd *cmd)
{
	t_list	*tmp;
	t_list	**arr;

	arr = cmd->arr;
	tmp = tkn->lst;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] == '|')
		{
			tmp->content = NULL;
			break ;
		}
		if (tmp->content)
		{
			ft_lstadd_back(&arr[cmd->count], ft_lstnew(ft_strdup(tmp->content)));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

/* return >> and filename out of t_token.lst to t_scmd.t_list ** */
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
		if (tmp->content && ((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strncmp(tmp->content, ">>", 1) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_lstnew(ft_strdup(tmp->content)));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

/* return > and filename out of t_token.lst to t_scmd.t_list ** */
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
		if (tmp->content && ((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strncmp(tmp->content, ">", 1) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_lstnew(ft_strdup(tmp->content)));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

/* return <>>> and filename out of t_token.lst to t_scmd.t_list ** */
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
		if (tmp->content && ((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strncmp(tmp->content, "<", 1) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_lstnew(ft_strdup(tmp->content)));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

/* return << limiter out of t_token.lst to t_scmd.t_list ** */
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
		if (tmp->content && ((char *)tmp->content)[0] == '|')
			break ;
		if (tmp->content && (!ft_strncmp(tmp->content, "<<", 2) || flag))
		{
			flag = flag ^ 1;
			ft_lstadd_back(&arr[cmd->count], ft_lstnew(ft_strdup(tmp->content)));
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

/* return int num of simple cmds out of t_token.str*/
int	ft_ctscmd(t_token *tkn)
{
	t_list	*tmp;
	int		i;

	tmp = tkn->lst;
	i = 0;
	while (tmp)
	{
		if (((char *)(tmp->content))[0] == '|')
			i++;
		tmp = tmp->next;
	}
	i++;
	return (i);
}

/* return 0 initialized and allocated t_scmd * */
t_scmd	*ft_init_scmd(t_token *tkn)
{
	t_scmd	*scmd;

	scmd = malloc(sizeof(t_scmd));
	if (!scmd)
		return (NULL);
	scmd->n_scmd = ft_ctscmd(tkn);
	scmd->arr = ft_calloc(scmd->n_scmd + 1, sizeof(t_list *));
	if (!scmd->arr)
	{
		ft_cleanup(tkn);
		return (NULL);
	}
	scmd->count = 0;
	scmd->arr[scmd->n_scmd] = NULL;
	return (scmd);
}

/* return t_scmd.lst ** of ordered simple cmds */
t_scmd	*ft_parse(t_token *tkn)
{
	t_scmd	*scmd;

	scmd = NULL;
	scmd = ft_init_scmd(tkn);
	while (scmd->count < scmd->n_scmd)
	{
		ft_gethdoc(tkn, scmd);
		ft_getredin(tkn, scmd);
		ft_getredout(tkn, scmd);
		ft_getappend(tkn, scmd);
		ft_getwords(tkn, scmd);
		scmd->count++;
	}
	return (scmd);
}

int	main(void)
{
	char	*str;
	t_token	*tkn;
	t_scmd	*scmd;

	str = "cat -e < Makefile << end| grep $USER >>out";
	tkn = ft_lex(str);
	scmd = ft_parse(tkn);
	ft_printf("counted %d simple command(s)\n", scmd->n_scmd);
	tmp_prtarrlst(scmd);
	ft_cleanup(tkn);
	return (0);
}
