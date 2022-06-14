/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:24:56 by etobias           #+#    #+#             */
/*   Updated: 2022/06/14 18:04:39 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*remove_quotes(char *str);
static size_t	get_size(char *str);

char	*delete_quotes(char *token)
{
	char	*temp;

	temp = token;
	token = remove_quotes(token);
	free(temp);
	return (token);
}

static char	*remove_quotes(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	temp;

	new_str = malloc(get_size(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			temp = i;
			i = i + 2 + (size_t)find_chr(str + i + 1, '\'');
			ft_memcpy(new_str + j, str + temp + 1, i - temp - 2);
			j += i - temp - 2;
		}
		if (str[i] == '\"')
		{
			temp = i;
			i = i + 2 + (size_t)find_chr(str + i + 1, '\"');
			ft_memcpy(new_str + j, str + temp + 1, i - temp - 2);
			j += i - temp - 2;
		}
		if (!str[i])
			break ;
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
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
