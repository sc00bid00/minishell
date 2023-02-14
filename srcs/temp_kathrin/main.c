// #include <unistd.h>
// #include <stdlib.h>

// int main(int argc, char **argv, char **envp)
// {
// 	char *p;
// 	p = malloc(sizeof(p));
// 	char *arg[] = {"echo", "$(USER)", NULL};
// 	execve("/bin/echo", arg, envp);
// 	write(1, "ciao", 4);
// 	return (0);
// }

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// #include "shell.h"

// void print_prompt1(void)
// {
//     fprintf(stderr, "$ ");
// }

// void print_prompt2(void)
// {
//     fprintf(stderr, "> ");
// }

// char *read_cmd(void)
// {
//     char buf[1024];
//     char *ptr = NULL;
//     char ptrlen = 0;

//     while(fgets(buf, 1024, stdin))
//     {
//         int buflen = strlen(buf);

//         if(!ptr)
//         {
//             ptr = malloc(buflen+1);
//         }
//         else
//         {
//             char *ptr2 = realloc(ptr, ptrlen+buflen+1);

//             if(ptr2)
//             {
//                 ptr = ptr2;
//             }
//             else
//             {
//                 free(ptr);
//                 ptr = NULL;
//             }
//         }

//         if(!ptr)
//         {
//             fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
//             return NULL;
//         }

//         strcpy(ptr+ptrlen, buf);

//         if(buf[buflen-1] == '\n')
//         {
//             if(buflen == 1 || buf[buflen-2] != '\\')
//             {
//                 return ptr;
//             }

//             ptr[ptrlen+buflen-2] = '\0';
//             buflen -= 2;
//             print_prompt2();
//         }

//         ptrlen += buflen;
//     }

//     return ptr;
// }

// int main(int argc, char **argv)
// {
//     char *cmd;

//     do
//     {
//         print_prompt1();

//         cmd = read_cmd();

//         if(!cmd)
//         {
//             exit(EXIT_SUCCESS);
//         }

//         if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
//         {
//             free(cmd);
//             continue;
//         }

//         if(strcmp(cmd, "exit\n") == 0)
//         {
//             free(cmd);
//             break;
//         }

//         printf("%s\n", cmd);

//         free(cmd);

//     } while(1);

//     exit(EXIT_SUCCESS);
// }


//  void   rl_gets(char *line)
// {
//     if (line)
//     {
//         free (line);
//         line = NULL;
//     }
//     if (line && *line)
//         add_history(line);
// }
// \033[36;1m&\033[0m 

//  char *read_line(void)
//  {
//   char *line = readline("");
//   if (line == NULL)
//   {
//     write(2, ERROR_1, sizeof(ERROR_1));
//     exit(1);
//   }
//   return (line);
// }
// bool newline(char *line)
// {
//     int i;

// 	i = 0;
// 	while (line[i] && line[i + 1])
//         i++;
//     if (line[i] == '\\')
//     	return (true);
// 	return (false);
// }

// int read_input(void)
// {
// 	char *line;

// 	if ((line = read_line()) != NULL && newline(line) == false)
//         printf("\033[36;1m$ \033[0m");
// 	else if ((line = read_line()) != NULL && newline(line) == true)
// 	{
//         printf("> ");
// 	}
// 	if (line && *line)
// 	{
// 		add_history(line);
// 		free (line);
// 	}
//   	return (0);
// }

// int main (int argc, char **argv, char **envp)
// {
//     printf("\033[36;1m$ \033[0m");
// 	while (1)
// 		read_input();
// }




int main (int argc, char **argv, char **envp)
{
    while (1)
		get_input();
}
