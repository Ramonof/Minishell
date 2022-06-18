/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:02 by etobias           #+#    #+#             */
/*   Updated: 2022/06/18 13:30:27 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_token(char *str, size_t *i);
static void	skip_quotes(char *str, size_t *i);
static int	find_redirection(char *str, size_t *i, size_t j);
static int	find_pipe(char *str, size_t *i, size_t j);

void	get_tokens(t_app *app)
{
	char	*token;
	size_t	i;

	i = 0;
	while (app->line[i])
	{
		token = get_next_token(app->line, &i);
		app->tokens = array_add(app->tokens, token);
		free(token);
	}
}

static char	*get_next_token(char *str, size_t *i)
{
	char	*token;
	size_t	j;

	while (str[*i] && is_space(str[*i]))
		(*i)++;
	j = *i;
	while (str[*i] && !is_space(str[*i]))
	{
		skip_quotes(str, i);
		if (find_redirection(str, i, j))
			break ;
		if (find_pipe(str, i, j))
			break ;
		(*i)++;
	}
	token = str_range_cpy(str, j, *i);
	return (token);
}

static void	skip_quotes(char *str, size_t *i)
{
	if (str[*i] == '\'')
	{
		if (find_chr(str + *i + 1, '\'') != -1)
			*i = *i + 1 + (size_t)find_chr(str + *i + 1, '\'');
	}
	if (str[*i] == '\"')
		if (find_chr(str + *i + 1, '\"') != -1)
			*i = *i + 1 + (size_t)find_chr(str + *i + 1, '\"');
}

static int	find_redirection(char *str, size_t *i, size_t j)
{
	if (str[*i] == '>')
	{
		if (*i != j)
			return (1);
		while (str[*i] == '>')
			(*i)++;
		return (1);
	}
	if (str[*i] == '<')
	{
		if (*i != j)
			return (1);
		while (str[*i] == '<')
			(*i)++;
		return (1);
	}
	return (0);
}

static int	find_pipe(char *str, size_t *i, size_t j)
{
	if (str[*i] == '|')
	{
		if (*i != j)
			return (1);
		while (str[*i] == '|')
			(*i)++;
		return (1);
	}
	return (0);
}
