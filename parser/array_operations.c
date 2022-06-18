/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:24:42 by etobias           #+#    #+#             */
/*   Updated: 2022/06/18 13:38:47 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_add(char **array, char *str)
{
	char	**new_array;
	size_t	i;
	size_t	len;

	len = array_len(array);
	if (len == 0)
		len++;
	new_array = malloc((len + 1) * sizeof(char *));
	if (!new_array)
		error_exit("malloc failed to allocate memory (array add)");
	i = 0;
	while (array && array[i])
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i++] = ft_strdup(str);
	if (str && !new_array[i - 1])
		error_exit("malloc failed to allocate memory (array add)");
	new_array[i] = NULL;
	if (array)
		free(array);
	return (new_array);
}

char	**array_remove(char **array, size_t index)
{
	char	**new_array;
	size_t	length;
	size_t	i;

	length = array_len(array) - 1;
	new_array = malloc(length * sizeof(char *));
	if (!new_array)
		error_exit("malloc failed to allocate memory (array remove)");
	i = 0;
	while (i < index)
	{
		new_array[i] = array[i];
		i++;
	}
	i++;
	while (array[i])
	{
		new_array[i - 1] = array[i];
		i++;
	}
	new_array[i - 1] = NULL;
	free(array[index]);
	free(array);
	return (new_array);
}
