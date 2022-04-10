#include "minishell.h"

void	alloc_commands(t_app *app)
{
	size_t	i;
	size_t	size;

	if (app->tokens == NULL)
	{
		app->cmd_array = NULL;
		return ;
	}
	i = 1;
	size = 1;
	while (app->tokens[i])
	{
		if (app->tokens[i][0] == '|')
			size++;
		if (app->tokens[i][0] == '<' || app->tokens[i][0] == '>')
			break ;
		i++;
	}
	app->cmd_number = size;
	app->pipe_number = size - 1;
	app->cmd_array = malloc(size * sizeof(t_command));
}

void	alloc_flags(t_app *app, size_t cmd_i, size_t end_i, size_t cmd_ind)
{
	size_t	i;
	size_t	size;

	size = 1;
	i = cmd_i;
	while (i < end_i)
	{
		if (app->tokens[i][0] == '-')
			size++;
		i++;
	}
	if (size == 1)
	{
		app->cmd_array[cmd_ind].cmd_flags = NULL;
		return ;
	}
	app->cmd_array[cmd_ind].cmd_flags = malloc(size * sizeof(char *));
	app->cmd_array[cmd_ind].cmd_flags[size - 1] = NULL;
}

void	alloc_args(t_app *app, size_t cmd_i, size_t end_i, size_t cmd_ind)
{
	size_t	i;
	size_t	size;

	size = 1;
	i = cmd_i;
	while (i < end_i)
	{
		if (app->tokens[i][0] != '-')
			size++;
		i++;
	}
	app->cmd_array[cmd_ind].cmd_args = malloc(size * sizeof(char *));
	app->cmd_array[cmd_ind].cmd_args[size - 1] = NULL;
}
