/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:24:56 by etobias           #+#    #+#             */
/*   Updated: 2022/06/16 00:23:56 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		copy_before_quotes(char *new_str, char *str,
					size_t *i, size_t *j);
static void		copy_in_quotes(char *new_str, char *str,
					size_t *i, size_t *j);
static size_t	get_size(char *str);

char	*delete_quotes(char *token)
{
	char	*new_token;
	size_t	i;
	size_t	j;

	new_token = malloc(get_size(token));
	i = 0;
	j = 0;
	while (token[i])
	{
		copy_before_quotes(new_token, token, &i, &j);
		copy_in_quotes(new_token, token, &i, &j);
	}
	new_token[j] = '\0';
	free(token);
	return (new_token);
}

static void	copy_before_quotes(char *new_str, char *str, size_t *i, size_t *j)
{
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			return ;
		new_str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
}

static void	copy_in_quotes(char *new_str, char *str, size_t *i, size_t *j)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '\"')
		quote = str[*i];
	else
		return ;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			(*i)++;
			return ;
		}
		new_str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
}

static size_t	get_size(char *str)
{
	size_t	i;
	size_t	size;
	size_t	deleted;

	size = 0;
	deleted = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			deleted += 2;
			i = i + 1 + (size_t)find_chr(str + i + 1, '\'');
		}
		if (str[i] == '\"')
		{
			deleted += 2;
			i = i + 1 + (size_t)find_chr(str + i + 1, '\"');
		}
		i++;
	}
	size = ft_strlen(str) - deleted + 1;
	return (size);
}
