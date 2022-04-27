#include "minishell.h"

char	**split_tokens(char **tokens, char *line)
{
	size_t	i;
	size_t	j;
	char	*temp;
	int		redirection;

	redirection = 0;
	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		j = i;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == '\'')
			{
				if (find_chr(line + i + 1, '\'') != -1)
					i = i + 1 + (size_t)find_chr(line + i + 1, '\'');
			}
			if (line[i] == '\"')
				if (find_chr(line + i + 1, '\"') != -1)
					i = i + 1 + (size_t)find_chr(line + i + 1, '\"');
			if (!redirection && (line[i] == '>' || line[i] == '<'))
			{
				redirection = 1;
				if (i != 0 && line[i - 1] != ' ')
				{
					temp = str_range_cpy(line, j, i);
					tokens = array_add(tokens, temp);
					free(temp);
				}
				j = i;
			}
			else if (redirection && (line[i] != '>' && line[i] != '<'))
			{
				redirection = 0;
				if (i != 0 && line[i - 1] != ' ')
				{
					temp = str_range_cpy(line, j, i);
					tokens = array_add(tokens, temp);
					free(temp);
				}
				j = i;
			}
			else
				i++;
		}
		temp = str_range_cpy(line, j, i);
		tokens = array_add(tokens, temp);
		free(temp);
	}
	return (tokens);
}
