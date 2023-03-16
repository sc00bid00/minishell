/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:15:12 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/16 11:15:15 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <minishell.h>

/* extern int exitstatus needs to be re-declared also here in order to
comply with linux compiler as well */
int exitstatus;

// /* Luca lex, parse, prexec, exec */
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	t_token	*tkn;
// 	t_scmd	*scmd;
// 	int		ret;

// 	(void)argc;
// 	(void)argv;
// 	// BASTARDS LIST:
// 	// heredoc not redirecting *** solved ***
// 	str = "< testfile | < testfile cat -e >> out << stop";
// 	// persisting hdoc *** solved ***
// 	// str = "< testfile | <testfile cat -e >> out << stop";
// 	// bad address *** solved ***
// 	// str = "< Makefile cat -e | wc -l >> out3 > out4";
// 	// token not recognized *** solved ***
// 	// str = "< Makefile wc -l << > stop out2 | ls";
// 	// str="env | grep \"$USER\" >> out2";
// 	ft_printf("%s\n", str);
// 	tkn = ft_lex(str);
// 	if (!tkn)
// 		return (2);
// 	scmd = ft_parse(tkn, envp);
// 	if(!scmd)
// 		return (1);
// 	ret = ft_pipe(scmd);
// 	ft_cleancmd(scmd);
// 	ft_cleanscmd(scmd);
// 	ft_cleantkn(tkn);
// 	return (ret);
// }

// /* Kathrin Main Nr.1 - readline */
// int main (int argc, char **argv, char **envp)
// {
// 	if (!argc && !argv && !envp)
// 		return (1);
// 	// char **copy;
// 	// copy = copy_env_to_heap(envp);
// 	// temp_print_envs(copy);
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


/* Kathrin Main Nr.2 - builtins */
// int main (int argc, char **argv, char **envp)
// {
// 	t_env 	*env;
// 	env = NULL;
// 	env = copy_envp_to_env(envp);
// 	create_env_array(env);
// 	builtin_pwd();
// 	print_env(env,0);
// 	builtin_cd(argc, argv, env);
// 	ft_error("minishell", argv[5], 0);
// 	builtin_env(argc, argv, env);
// 	builtin_echo(argc, argv, env);
// 	print_env(env,0);
// 	ft_ms_lstclear(env);
// 	free (env);
// }
