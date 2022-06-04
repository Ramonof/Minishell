#include "minishell.h"

void	sig_quit(int code)
{
	code += 0;
}

void	sig_int(int code)
{
	ft_putstr_fd("\n>> ", 1);
	code += 0;
}
