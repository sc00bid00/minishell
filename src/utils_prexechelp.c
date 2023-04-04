/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prexechelp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:33:28 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/04 18:50:02 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_helppaths(t_cmd *cmd, char **arr, int j)
{
	char	*tmp;

	tmp = ft_strjoin(arr[j], "/");
	cmd->path = ft_strjoin(tmp, cmd->arr[0]);
	free(tmp);
}

void	ft_helpisheredoc(t_scmd	*scmd, t_cmd **tmp)
{
	char	tmp_s[2];

	tmp_s[0] = 65 + scmd->count;
	tmp_s[1] = '\0';
	(*tmp)->in_name = ft_strjoin("/var/tmp/.hdoc_", tmp_s);
	(*tmp)->fd_in = open((*tmp)->in_name, O_RDWR | O_CREAT, 0644);
}

void	ft_helpisheredoc_2(t_cmd *tmp)
{
	close(tmp->fd_in);
	if (!(tmp->stat & 0b000101))
		tmp->stat |= 0b000010;
}

void	ft_hdocdollar(char **str, t_scmd *scmd)
{
	t_list	*lst;
	t_list	*tmp;
	char	*s;

	lst = NULL;
	lst = ft_strtolstecho(*str);
	tmp = lst;
	while (tmp)
	{
		if (tmp->content && ((char *)tmp->content)[0] == '$'
			&& ((char *)tmp->content)[1])
		{
			s = ft_strdup(&((char *)tmp->content)[1]);
			free(tmp->content);
			tmp->content = ft_dollarsubst2(s, scmd);
			free(s);
		}
		tmp = tmp->next;
	}
	free(*str);
	*str = ft_lsttostr(lst);
	ft_cleanlst(lst);
}

char	*ft_dollarsubst2(char *str, t_scmd *scmd)
{
	t_env	*env_var;
	char	*tmp;

	tmp = NULL;
	if (str && str[0] == '0')
	{
		env_var = ret_var(&scmd->env, "SHELL");
		if (env_var)
			tmp = ft_strjoin(env_var->var_content, &str[1]);
	}
	else if (str && ft_isdigit(str[0]))
		tmp = ft_strdup(&str[1]);
	else if (str)
	{
		env_var = ret_var(&scmd->env, str);
		if (env_var)
			tmp = ft_strdup(env_var->var_content);
	}
	return (tmp);
}
