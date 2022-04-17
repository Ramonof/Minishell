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

#include "minishell.h"

static void	replace_env_vars(char **tokens);
static void	get_commands(t_app *app);
static void	get_args(t_app *app, size_t cmd_i, size_t end_i, size_t cmd_ind);

void	fill_commands_array(t_app *app)
{
	app->tokens = ft_split(app->line, ' ');
	replace_env_vars(app->tokens);
	alloc_commands(app);
	get_commands(app);
}

static void	replace_env_vars(char **tokens)
{
	size_t	i;
	char	*env_var;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '$')
		{
			env_var = getenv(tokens[i] + 1);
			free(tokens[i]);
			tokens[i] = env_var;
		}
		i++;
	}
}

static void	get_commands(t_app *app)
{
	size_t	i;
	size_t	array_index;
	size_t	cmd_i;

	array_index = 0;
	cmd_i = 0;
	app->cmd_array[array_index++].cmd = app->tokens[0];
	i = 1;
	while (app->tokens[i])
	{
		if (app->tokens[i][0] == '|')
		{
			get_args(app, cmd_i, i, array_index - 1);
			app->cmd_array[array_index].cmd = app->tokens[i + 1];
			cmd_i = i + 1;
			array_index++;
		}
		if (app->tokens[i][0] == '<' || app->tokens[i][0] == '>')
			break ;
		i++;
	}
	get_args(app, cmd_i, i, array_index - 1);
}

static void	get_args(t_app *app, size_t cmd_i, size_t end_i, size_t cmd_ind)
{
	size_t	i;
	size_t	arg_i;

	alloc_args(app, cmd_i, end_i, cmd_ind);
	app->cmd_array[cmd_ind].cmd_args[0] = app->tokens[cmd_i];
	i = cmd_i + 1;
	arg_i = 1;
	while (i < end_i)
	{
		app->cmd_array[cmd_ind].cmd_args[arg_i] = app->tokens[i];
		arg_i++;
		i++;
	}
}
