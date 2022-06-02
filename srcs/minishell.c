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

int	main(int argc, char **argv, char **envp)
{
	//int	fd;
	char	*line;
	char	**envpd;
	t_app	app;
	t_data	data;


	app.last_cmd_result = -1;

	if (argc || argv || envp)
		printf("pass\n");
	envpd = init_env(envp);
	if (!envpd)
		printf("No envp\n");
	data.env = envpd;
	app.data = &data;
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

		start_parser(&app);

		start_my_execute(app, envpd, &data);
		envpd = data.env;
		/**/
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(">> ");
  	}
	// ************* (183)
	return (0);
}
