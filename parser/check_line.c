#include "minishell.h"

static int	is_space(char c);

int	check_line(char *line)
{
	size_t	i;

	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_space(line[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	is_space(char c)
{
	return (c <= ' ' || c > 126);
}