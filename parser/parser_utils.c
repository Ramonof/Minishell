#include "minishell.h"

size_t	array_len(char **array)
{
	size_t	size;

	if (!array)
		return 0;
	size = 1;
	while (array[size - 1])
		size++;
	return (size);
}

char	**array_add(char **array, char *str)
{
	char	**new_array;
	size_t	i;

	new_array = malloc((array_len(array) + 1) * sizeof(char *));
	i = 0;
	while (array[i])
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i++] = ft_strdup(str);
	new_array[i] = NULL;
	free(array);
	return (new_array);
}

char	*str_range_cpy(char *str, size_t start, size_t end)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = malloc(end - start + 2);
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

	beginning = str_range_cpy(str, 0, start - 1);
	ending = str_range_cpy(str, end + 1, ft_strlen(str) - 1);
	new_str = ft_strjoin(beginning, to_insert);
	temp = new_str;
	new_str = ft_strjoin(new_str, ending);
	free(temp);
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
