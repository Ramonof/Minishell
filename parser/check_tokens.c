/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:24:50 by etobias           #+#    #+#             */
/*   Updated: 2022/06/08 00:24:51 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirs_pipes(char **tokens);
static int	check_redirect(char **tokens, size_t i);
static int	check_pipe(char **tokens, size_t i);
static int	check_next_token(char *token);

int	check_tokens(t_app *app)
{
	return (check_redirs_pipes(app->tokens));
}

static int	check_redirs_pipes(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (!check_redirect(tokens, i))
				return (0);
		}
		else if (tokens[i][0] == '|')
		{
			if (!check_pipe(tokens, i))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_redirect(char **tokens, size_t i)
{
	if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], "<<")
		|| !ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
	{
		if (!check_next_token(tokens[i + 1]))
			return (0);
	}
	else
	{
		error_sentence(UNEXPECTED_SYMBOL_ERROR, SYNTAX_ERROR_CODE);
		return (0);
	}
	return (1);
}

static int	check_pipe(char **tokens, size_t i)
{
	if (!ft_strcmp(tokens[i], "|"))
	{
		if (!check_next_token(tokens[i + 1]))
			return (0);
	}
	else
	{
		error_sentence(UNEXPECTED_SYMBOL_ERROR, SYNTAX_ERROR_CODE);
		return (0);
	}
	return (1);
}

static int	check_next_token(char *token)
{
	if (!token)
	{
		error_sentence(NO_FILE_MENTIONED_ERROR, SYNTAX_ERROR_CODE);
		return (0);
	}
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, "<<")
		|| !ft_strcmp(token, ">") || !ft_strcmp(token, ">>"))
	{
		error_sentence(UNEXPECTED_SYMBOL_ERROR, SYNTAX_ERROR_CODE);
		return (0);
	}
	if (!ft_strcmp(token, "|"))
	{
		error_sentence(UNEXPECTED_SYMBOL_ERROR, SYNTAX_ERROR_CODE);
		return (0);
	}
	return (1);
}
