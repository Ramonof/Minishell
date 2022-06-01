#include "minishell.h"

static void	alloc_memory(t_app *app);
static void	init_command(t_command *cmd);

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
	app->cmds = malloc((size + 1) * sizeof(t_command *));
	alloc_memory(app);
}

static void	alloc_memory(t_app *app)
{
	size_t	i;

	i = 0;
	while (i < (size_t)app->cmd_number)
	{
		app->cmds[i] = malloc(sizeof(t_command));
		init_command(app->cmds[i]);
		i++;
	}
	app->cmds[i] = NULL;
}

static void	init_command(t_command *cmd)
{
	cmd->input_desc = 0;
	cmd->output_desc = 1;
	cmd->args = NULL;
}

void	get_cmds(t_app *app)
{
	size_t	cmd_i;
	size_t	i;

	cmd_i = 0;
	i = 0;
	app->cmds[cmd_i]->args = NULL;
	while (app->tokens[i])
	{
		if (app->tokens[i][0] == '|')
			cmd_i++;
		else if (app->tokens[i][0] == '<' || app->tokens[i][0] == '>')
			handle_redirects(app, i++, cmd_i);
		else
			app->cmds[cmd_i]->args = array_add(app->cmds[cmd_i]->args,
					app->tokens[i]);
		i++;
	}
}
