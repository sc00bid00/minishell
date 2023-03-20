
#include <minishell.h>

bool is_numeric(char *str)
{
	int i;

	i = 0;
	while (str[i])
}

int builtin_exit(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
	int i;

	i = 0;
	if (cmd->arr && cmd->arr[i] && cmd->arr[2] == NULL)
	{
		if (!is_numeric(cmd->arr[i]))
		exitstatus = 128;
	}
	else if (cmd->)
	return (0);
}
