#include "minishell.h"
#include "get_next_line.h"

static int	handle_input(t_app *app, size_t *i);
static int	get_input_file(char **tokens, size_t start, size_t end);
static int	handle_output(t_app *app, size_t *i);
static int	get_output_file(char **tokens, size_t start, size_t end);

void	handle_redirects(t_app *app, size_t *i, size_t cmd_i)
{
	if (app->tokens[*i][0] == '<')
		app->cmds[cmd_i]->input_desc = handle_input(app, i);
	else if (app->tokens[*i][0] == '>')
		app->cmds[cmd_i]->output_desc = handle_output(app, i);
}

static int	handle_input(t_app *app, size_t *i)
{
	size_t	j;
	int		found_redir;
	int		fd;

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
	fd = get_input_file(app->tokens, *i, j - 1);
	*i = j - 1;
	return (fd);
}

static int	get_input_file(char **tokens, size_t start, size_t end)
{
	int		fd;

	while (start != end + 2)
	{
		fd = open(tokens[start], O_CREAT | O_RDONLY, 0666);
		close(fd);
		start += 2;
	}
	fd = open(tokens[start - 2], O_RDONLY);
	return (fd);
}

static int	handle_output(t_app *app, size_t *i)
{
	size_t	j;
	int		found_redir;
	int		fd;

	(*i)++;
	j = *i;
	found_redir = 1;
	while (app->tokens[j])
	{
		if (app->tokens[j][0] != '>')
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
	fd = get_output_file(app->tokens, *i, j - 1);
	*i = j - 1;
	return (fd);
}

static int	get_output_file(char **tokens, size_t start, size_t end)
{
	int		fd;

	while (start != end + 2)
	{
		fd = open(tokens[start], O_CREAT | O_WRONLY, 0666);
		close(fd);
		start += 2;
	}
	fd = open(tokens[start - 2], O_WRONLY);
	return (fd);
}
