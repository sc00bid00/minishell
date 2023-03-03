/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:06:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/03/03 11:24:38 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*tkn;
	t_scmd	*scmd;
	int		ret;

	if (!argc && !argv)
		return (1);
	// BASTARDS LIST:
	// heredoc not redirecting *** solved ***
	str = "< testfile | < testfile cat -e >> out << stop";
	// persisting hdoc *** solved ***
	// str = "< testfile | <testfile cat -e >> out << stop";
	// bad address *** solved ***
	// str = "< Makefile cat -e | wc -l >> out3 > out4";
	// token not recognized *** solved ***
	// str = "< Makefile wc -l << > stop out2 | ls";
	// str="env | grep \"$USER\" >> out2";
	ft_printf("%s\n", str);
	tkn = ft_lex(str);
	if (!tkn)
		return (2);
	scmd = ft_parse(tkn, envp);
	if(!scmd)
		return (1);
	ret = ft_pipe(scmd);
	ft_cleancmd(scmd);
	ft_cleanscmd(scmd);
	ft_cleantkn(tkn);
	return (ret);
}

// int main (int argc, char **argv, char **envp)
// {
// 	char **copy;
// 	copy = copy_env_to_heap(envp);
// 	temp_print_envs(copy);
// 	signal(SIGQUIT, SIG_IGN);
//     while (1)
// 	{
// 		setup_sigint();
// 		get_input();
// 		// restore_terminal();
// 		// get_input();
// 		//setup_sigexec(); put back default signals
// 		// restore_terminal();
// 	}
// 	return (0);
// }

// int main (int argc, char **argv, char **envp)
// {
// 	t_env 	*env;
// 	env = NULL;
// 	env = copy_envp_to_env(envp);
// 	create_env_array(env);
	// builtin_pwd();
	// print_env(env);
	// builtin_cd(argc, argv, env);
	// ft_error("minishell", argv[5], 0);
	// builtin_env(argc, argv, env);
	// builtin_echo(argc, argv, env);
	// print_env(env);
	// ft_ms_lstclear(env);
	// free (env);
// }
