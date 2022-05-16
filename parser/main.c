#include "minishell.h"

int	main()
{
	//int	fd;
	char *line;
	t_app app;

	// readline working
	line = readline(">> ");
	while (line)
	{
		app.line = line;
		printf("Line: %s\n", app.line);

		if (strlen(line) > 0)
		{
			add_history(line);
			start_parser(&app);
    	}

		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(">> ");
  	}
	return (0);
}