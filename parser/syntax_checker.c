#include "minishell.h"

static void	check_quotes(char *line);
static int	find_end_quote(char *line, char quote, size_t *i);

void	start_syntax_checker(t_app *app)
{
	check_quotes(app->line);
}

static void	check_quotes(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!find_end_quote(line, line[i], &i))
				error_exit("error: unclosed quotes\n");
		}
		i++;
	}
}

static int	find_end_quote(char *line, char quote, size_t *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == quote)
			return (1);
		(*i)++;
	}
	return (0);
}
