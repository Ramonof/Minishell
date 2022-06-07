/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:14 by etobias           #+#    #+#             */
/*   Updated: 2022/06/08 00:25:15 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *line);
static int	find_end_quote(char *line, char quote, size_t *i);

int	start_syntax_checker(t_app *app)
{
	return (check_quotes(app->line));
}

static int	check_quotes(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!find_end_quote(line, line[i], &i))
			{
				error_sentence(UNCLOSED_QUOTES_ERROR, SYNTAX_ERROR_CODE);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	find_end_quote(char *line, char quote, size_t *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == quote)
			return (1);
		(*i)++;
	}
	return (0);
}
