
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



int main (int argc, char **argv, char **envp)
{
	char ** copy;
	copy = copy_env_to_heap(envp);
	temp_print_envs(copy);
	signal(SIGQUIT, SIG_IGN);
    while (1)
	{
		setup_sigint();
		get_input();
		// restore_terminal();
	}
	return (0);
}
