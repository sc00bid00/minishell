#include <lexer.h>

int	main(void)
{
	ft_printf("$USER = %s\n", getenv("USER"));
	ft_printf("$UNDECLARED = %s\n", getenv("UNDECLARED"));
	return (0);
}
