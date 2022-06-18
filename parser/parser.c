/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:11 by etobias           #+#    #+#             */
/*   Updated: 2022/06/18 22:58:15 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*remove_spaces(char *line);
static size_t	get_size(char *line);

int	start_parser(t_app *app)
{
	int	code;

	app->tokens = NULL;
	app->cmds = NULL;
	app->line = remove_spaces(app->line);
	code = 0;
	if (start_syntax_checker(app))
	{
		get_tokens(app);
		if (check_tokens(app))
		{
			expand_tokens(app);
			alloc_cmds(app);
			get_cmds(app);
			code = 1;
		}
	}
	free_tokens(app);
	return (code);
}

static char	*remove_spaces(char *line)
{
	char	*temp;
	char	*new_line;
	size_t	size;
	size_t	i;

	temp = line;
	size = get_size(line);
	new_line = malloc(size);
	if (!new_line)
		error_exit("malloc failed to allocate memory (delete spaces)");
	while (is_space(*line))
		line++;
	i = 0;
	while (i < size - 1)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(temp);
	return (new_line);
}

static size_t	get_size(char *line)
{
	size_t	size;

	while (is_space(*line))
		line++;
	size = ft_strlen(line) - 1;
	while (is_space(line[size]))
		size--;
	return (size + 2);
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

	if (!app->cmds)
		return ;
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
