/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:24:56 by etobias           #+#    #+#             */
/*   Updated: 2022/06/08 00:24:56 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*str_remove_char(char *str, char to_delete);
static size_t	get_size(char *str, char to_delete);

char	*delete_quotes(char *token)
{
	char	*temp;

	temp = token;
	token = str_remove_char(token, '\'');
	free(temp);
	temp = token;
	token = str_remove_char(token, '\"');
	free(temp);
	return (token);
}

static char	*str_remove_char(char *str, char to_delete)
{
	char	*new_str;
	size_t	size;
	size_t	i;
	size_t	j;

	size = get_size(str, to_delete);
	new_str = malloc(size + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != to_delete)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

static size_t	get_size(char *str, char to_delete)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != to_delete)
			size++;
		i++;
	}
	return (size);
}
