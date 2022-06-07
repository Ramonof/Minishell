/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:11 by etobias           #+#    #+#             */
/*   Updated: 2022/06/08 00:25:11 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_parser(t_app *app)
{
	int	code;

	app->tokens = NULL;
	app->cmds = NULL;
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
