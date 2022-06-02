#include "minishell.h"

void	start_parser(t_app *app)
{
	start_syntax_checker(app);
	app->tokens = NULL;
	get_tokens(app);
	check_tokens(app);
	expand_tokens(app);
	for (int i = 0; app->tokens[i]; i++)
		printf("%s\n", app->tokens[i]);
	alloc_cmds(app);
	get_cmds(app);
	free_tokens(app);
}

void	free_tokens(t_app *app)
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
		while (app->cmds[i]->args[j])
		{
			free(app->cmds[i]->args[j]);
			j++;
		}
		free(app->cmds[i]->args);
		free(app->cmds[i]);
		i++;
	}
	free(app->cmds);
}
