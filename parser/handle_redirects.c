#include "minishell.h"
#include "get_next_line.h"

static int	get_input_desc(t_app *app, size_t i, size_t cmd_i);
static int	get_heredoc(t_app *app, size_t i, size_t cmd_i);
static int	get_output_desc(t_app *app, size_t i, size_t cmd_i, int append);

void	handle_redirects(t_app *app, size_t i, size_t cmd_i)
{
	if (ft_strcmp(app->tokens[i], "<") == 0)
		app->cmds[cmd_i]->input_desc = get_input_desc(app, ++i, cmd_i);
	else if (ft_strcmp(app->tokens[i], "<<") == 0)
		app->cmds[cmd_i]->input_desc = get_heredoc(app, ++i, cmd_i);
	else if (ft_strcmp(app->tokens[i], ">") == 0)
		app->cmds[cmd_i]->output_desc = get_output_desc(app, ++i, cmd_i, 0);
	else if (ft_strcmp(app->tokens[i], ">>") == 0)
		app->cmds[cmd_i]->output_desc = get_output_desc(app, ++i, cmd_i, 1);
}

static int	get_input_desc(t_app *app, size_t i, size_t cmd_i)
{
	int	fd;

	if (app->cmds[cmd_i]->input_desc > 2)
		close(app->cmds[cmd_i]->input_desc);
	fd = open(app->tokens[i], O_RDONLY);
	if (fd < 0)
	{
		free_tokens(app);
		free_cmds(app);
		error_exit("unable to open file\n");
	}
	return (fd);
}

static int	get_heredoc(t_app *app, size_t i, size_t cmd_i)
{
	int		fd;
	char	*buf;

	if (app->cmds[cmd_i]->input_desc > 2)
		close(app->cmds[cmd_i]->input_desc);
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &buf, 0) < 0)
			error_exit("error: can't read heredoc\n");
		if (!ft_strncmp(app->tokens[i], buf, ft_strlen(app->tokens[i]) + 1))
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	get_next_line(0, NULL, 0);
	free(buf);
	close(fd);
	fd = open(HEREDOC, O_RDONLY);
	return (fd);
}

static int	get_output_desc(t_app *app, size_t i, size_t cmd_i, int append)
{
	int	fd;
	int	flags;

	if (app->cmds[cmd_i]->output_desc > 2)
		close(app->cmds[cmd_i]->output_desc);
	if (append)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	fd = open(app->tokens[i], flags, 0000644);
	return (fd);
}
