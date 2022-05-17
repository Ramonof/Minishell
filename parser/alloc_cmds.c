#include "minishell.h"

static char	**get_args(t_app *app, size_t start, size_t end);

void	alloc_cmds(t_app *app)
{
	size_t	i;
	size_t	size;

	if (app->tokens == NULL)
	{
		app->cmds = NULL;
		return ;
	}
	i = 1;
	size = 1;
	while (app->tokens[i])
	{
		if (app->tokens[i][0] == '|')
			size++;
		i++;
	}
	app->cmd_number = size;
	app->pipe_number = size - 1;
	app->cmds = malloc((size + 1) * sizeof(char **));
	app->cmds[size] = NULL;
}

void	get_cmds(t_app *app)
{
	size_t	array_i;
	size_t	cmd_i;
	size_t	i;

	array_i = 0;
	cmd_i = 0;
	i = 1;
	while (app->tokens[i])
	{
		if (app->tokens[i][0] == '|')
		{
			app->cmds[cmd_i] = get_args(app, array_i, i);
			array_i = i + 1;
			cmd_i++;
		}
		if (app->tokens[i][0] == '<' || app->tokens[i][0] == '>')
			break ;
		i++;
	}
	app->cmds[cmd_i] = get_args(app, array_i, i);
}

static char	**get_args(t_app *app, size_t start, size_t end)
{
	size_t	i;
	size_t	arg_i;
	char	**args;

	args = malloc((end - start + 2) * sizeof(char *));
	args[0] = ft_strdup(app->tokens[start]);
	i = start + 1;
	arg_i = 1;
	while (i < end)
	{
		args[arg_i] = ft_strdup(app->tokens[i]);
		arg_i++;
		i++;
	}
	args[arg_i] = NULL;
	return (args);
}
