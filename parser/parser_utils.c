/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:07 by etobias           #+#    #+#             */
/*   Updated: 2022/06/08 00:25:08 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	array_len(char **array)
{
	size_t	size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	size++;
	return (size);
}

char	*str_range_cpy(char *str, size_t start, size_t end)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	new_str = malloc(end - start + 3);
	i = start;
	j = 0;
	while (str[i] && i < end)
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*str_insert(char *str, char *to_insert, size_t start, size_t end)
{
	char	*new_str;
	char	*beginning;
	char	*ending;
	char	*temp;

	beginning = str_range_cpy(str, 0, start);
	ending = str_range_cpy(str, end + 1, ft_strlen(str));
	if (to_insert)
	{
		new_str = ft_strjoin(beginning, to_insert);
		temp = new_str;
		new_str = ft_strjoin(new_str, ending);
		free(temp);
	}
	else
	{
		new_str = ft_strjoin(beginning, ending);
	}
	free(beginning);
	free(ending);
	return (new_str);
}

int	find_chr(const char *s, int c)
{
	char	find;
	int		i;

	find = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == find)
			return (i);
		i++;
	}
	if (s[i] == find)
		return (i);
	return (-1);
}
