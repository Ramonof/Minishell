#include "minishell.h"

static char	*expand_token(t_app *app, char *token);
static char	*delete_quotes(char *token);
static char	*str_remove_char(char *str, char to_delete);

void	expand_tokens(t_app *app, char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = expand_token(app, tokens[i]);
		tokens[i] = delete_quotes(tokens[i]);
		i++;
	}
}

static char	*expand_token(t_app *app, char *token)
{
	char	*temp;
	char	*env;
	size_t	i;
	size_t	j;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			if (find_chr(token + i + 1, '\'') != -1)
				i = i + 1 + (size_t)find_chr(token + i + 1, '\'');
		if (token[i] == '$')
		{
			j = ++i;
			if (token[i] == '?')
			{
				// need to fix $PATH$? and $?$PATH case
				env = ft_itoa(app->last_cmd_result);
				temp = token;
				token = env;
				free(temp);
				i++;
			}
			else
			{
				while (token[i] && token[i] != '\"' && token[i] != '\'' && token[i] != ' '
					&& token[i] != '$')
				i++;
				temp = str_range_cpy(token, j, i);
				env = getenv(temp);
				token = str_insert(token, env, j, i - 1);
			}
		}
		i++;
	}
	return (token);
}

static char	*delete_quotes(char *token)
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

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != to_delete)
			size++;
		i++;
	}
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
