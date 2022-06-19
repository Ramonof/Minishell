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

static void	free_pwd_env(t_data *data);

t_status	g_status;

void	main_cycle(t_app app, char **envpd, t_data *data)
{
	while (app.line)
	{
		if (ft_strlen(app.line) > 0)
		{
			if (check_line(app.line))
			{
				add_history(app.line);
				if (start_parser(&app))
				{
					start_my_execute(app, envpd, data);
				}
				free_cmds(&app);
			}
		}
		envpd = data->env;
		if (app.line)
		{
			free(app.line);
			app.line = NULL;
		}
		set_signal_handling();
		app.line = readline(">> ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**envpd;
	t_app	app;
	t_data	data;

	g_status.exit_code = 0;
	g_status.pid = 0;
	envpd = 0;
	if ((argc || argv) && envp)
		envpd = init_env(envp);
	if (!envpd)
		error_sentence(MALLOC_ERROR, MALLOC_ERROR_CODE);
	data.env = envpd;
	app.data = &data;
	data.pwd = ft_strdup(find_pwd(envp));
	if (!data.pwd)
		error_sentence(MALLOC_ERROR, MALLOC_ERROR_CODE);
	set_signal_handling();
	app.line = readline(">> ");
	main_cycle(app, envpd, &data);
	free_pwd_env(&data);
	return (0);
}

static void	free_pwd_env(t_data *data)
{
	size_t	i;

	if (data->pwd)
		free(data->pwd);
	i = 0;
	while (data->env && data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	if (data->env)
		free(data->env);
}
