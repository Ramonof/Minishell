/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:55:21 by mrolande          #+#    #+#             */
/*   Updated: 2022/03/23 10:55:21 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

static void	clean_memory(t_app *app);

int	main(int argc, char **argv, char **envp)
{
	//int	fd;
	char *line;
	t_app app;

	app.last_cmd_result = -1;

	if (argc || argv)
		printf("pass\n");

	// readline working
	line = readline(">> ");
	while (line)
	{
		if (strlen(line) > 0)
		{
			add_history(line);
    	}
		/**/
		app.line = line;

		printf("Line: %s\n", app.line);

		fill_commands_array(&app);

		start_my_execute(app, envp);
		/**/
		if (line)
		{
			free(line);
			line = NULL;
			clean_memory(&app);
		}
		line = readline(">> ");
  	}
	// ************* (183)
	return (0);
}

static void	clean_memory(t_app *app)
{
	size_t	i;

	i = 0;
	while (app->tokens[i])
	{
		free(app->tokens[i]);
		i++;
	}
}
