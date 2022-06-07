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

static void	set_signal_handling();
static void	reset_signal_handling();

int	g_status = 0;

char	*find_pwd(char **envp)
{
	if (!envp)
		return (NULL);
	while (ft_strncmp("PWD=", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 4);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envpd;
	t_app	app;
	t_data	data;

	if ((argc || argv ) && envp)
		envpd = init_env(envp);
	if (!envpd)
		error_sentence(MALLOC_ERROR, MALLOC_ERROR_CODE);
	data.env = envpd;
	app.data = &data;
	// data.pwd = getcwd(NULL, 0);
	data.pwd = ft_strdup(find_pwd(envp));
	if (!data.pwd)
		error_sentence(MALLOC_ERROR, MALLOC_ERROR_CODE);
	set_signal_handling();
	app.line = readline(">> ");
	reset_signal_handling();
	while (app.line)
	{
		printf("Line: %s\n", app.line);
		if (strlen(app.line) > 0)
		{
			if (check_line(app.line))
			{
				add_history(app.line);
				start_parser(&app);
				start_my_execute(app, envpd, &data);
				free_cmds(&app);
			}
		}
		envpd = data.env;
		if (app.line)
		{
			free(app.line);
			app.line = NULL;
		}
		set_signal_handling();
		app.line = readline(">> ");
		reset_signal_handling();
	}
	free(data.pwd);
	for (int i = 0; data.env[i]; i++)
		free(data.env[i]);
	free(data.env);
	// ************* (183)
	return (0);
}

static void	set_signal_handling()
{
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
}

static void	reset_signal_handling()
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
