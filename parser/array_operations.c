#include "minishell.h"

char	**array_remove(char **array, size_t index)
{
	char	**new_array;
	size_t	length;
	size_t	i;

	length = array_len(array) - 1;
	new_array = malloc(length * sizeof(char *));
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
