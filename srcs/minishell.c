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
	char *line;
	t_app app;

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

		printf("Line: %s\n\n", app.line);

		fill_commands_array(&app);

		my_execute(app, envp);
		/**/
		if (line)
		{
			printf("%s\n", line);
			free(line);
		}
		line = readline(">> ");
  	}
	// ************* (183)
	return (0);
}
