#include "minishell.h"

static void	free_tokens(t_app *app);

void	start_parser(t_app *app)
{
	app->tokens = NULL;
	get_tokens(app);
	expand_tokens(app);
	alloc_cmds(app);
	get_cmds(app);
	free_tokens(app);
}

static void	free_tokens(t_app *app)
{
	size_t	i;

	if (!app->tokens)
		return ;
	i = 0;
	while (app->tokens[i])
		free(app->tokens[i++]);
	free(app->tokens);
	app->tokens = NULL;
}

void	free_cmds(t_app *app)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (app->cmds[i])
	{
		j = 0;
		while (app->cmds[i][j])
		{
			free(app->cmds[i][j]);
			j++;
		}
		free(app->cmds[i]);
		i++;
	}
	free(app->cmds);
}
