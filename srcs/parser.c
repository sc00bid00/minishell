/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:22:46 by lsordo            #+#    #+#             */
/*   Updated: 2023/02/28 16:45:28 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

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
	if (!ft_prexec(scmd))
		return (NULL);
	return (scmd);
}
