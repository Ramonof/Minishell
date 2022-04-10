#include "minishell.h"

int main()
{
	char *line = "ls -a you -l | cd -d my arg -s | cat -v another_arg";
	t_app app;

	app.line = line;

	printf("Line: %s\n\n", app.line);

	fill_commands_array(&app);
	printf("--- Tokens ---\n");
	for (size_t i = 0; app.tokens[i]; i++)
	{
		printf("token: %s\n", app.tokens[i]);
	}
	printf("\n");
	printf("--- Commands ---\n");
	for (size_t i = 0; i < app.cmd_number; i++)
	{
		printf("command: %s\n", app.cmd_array[i].cmd);

		if (app.cmd_array[i].cmd_flags == NULL)
			continue;
		for (size_t j = 0; app.cmd_array[i].cmd_flags[j]; j++)
		{
			printf("flag: %s\n", app.cmd_array[i].cmd_flags[j]);
		}
		for (size_t j = 0; app.cmd_array[i].cmd_args[j]; j++)
		{
			printf("arg: %s\n", app.cmd_array[i].cmd_args[j]);
		}
		printf("\n");
	}
}