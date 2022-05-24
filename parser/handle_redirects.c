#include "minishell.h"
#include "get_next_line.h"

static void	handle_input(t_app *app, size_t *i);
static int	write_files(char **tokens, size_t start, size_t end);
static void	handle_output(t_app *app, size_t *i);

void	handle_redirects(t_app *app, size_t *i)
{
	if (app->tokens[*i][0] == '<')
		handle_input(app, i);
	else if (app->tokens[*i][0] == '>')
		handle_output(app, i);
	// rewrite get_cmds() to handle redirects correctly
	// create init() for t_command
	// redirect handling works between pipes and looks for < or >
	// if found tries to count redirects
	// then opens and writes files in sequence with get_next_line()
	// the leftmost / rightmost file is opened and desc is put in the command input / output desc
	
	// rewrite parser to handle cases like "cat < some_file -e"
}

static void	handle_input(t_app *app, size_t *i)
{
	size_t	j;
	int		found_redir;

	(*i)++;
	j = *i;
	found_redir = 1;
	while (app->tokens[j])
	{
		if (app->tokens[j][0] != '<')
		{
			if (found_redir)
				found_redir = 0;
			else
				break ;
		}
		else
			found_redir = 1;
		j++;
	}
	close(write_files(app->tokens, j - 1, *i));
	*i = j - 1;
}

static int	write_files(char **tokens, size_t start, size_t end)
{
	int		from;
	int		to;
	char	*line;

	while (start != end)
	{
		from = open(tokens[start], O_RDONLY);
		to = open(tokens[start - 2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		while (get_next_line(from, &line, 0) > 0)
		{
			write(to, line, ft_strlen(line));
		}
		close(from);
		close(to);
		start -= 2;
	}
	return (open(tokens[start], O_RDONLY));
}

static void	handle_output(t_app *app, size_t *i)
{
	
}
