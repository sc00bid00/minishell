/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:33:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/16 09:21:54 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_start(char **envp, t_env *env, char *input)
{
	int		ret;
	t_token	*tkn;
	t_scmd	*scmd;

	tkn = ft_lex(input, env);
	if (!tkn)
		return (2);
	scmd = ft_parse(tkn, envp, env);
	if (!scmd)
		return (1);
	tmp_prtcmd(scmd);
	ft_exec(scmd);
	ret = scmd->flag;
	ft_cleancmd(scmd);
	ft_cleanscmd(scmd);
	ft_cleantkn(tkn);
	return (ret);
}

char	*read_line(void)
{
	char	*line;

	line = readline("\033[36;1mminishell$ \033[0m");
	if (line == NULL)
		exit(1);
	return (line);
}

int	get_input(char **envp, t_env *env)
{
	char	*input;

	input = read_line();
	if (input != NULL)
	{
		if (input && *input)
			add_history(input);
		exitstatus = ft_start(envp, env, input);
		free(input);
	}
	return (exitstatus);
}

int	test_get_input(char **envp, t_env *env, char *input)
{
	if (input)
		exitstatus = ft_start(envp, env, input);
	return (exitstatus);
}
