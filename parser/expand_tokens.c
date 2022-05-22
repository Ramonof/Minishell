#include "minishell.h"

static char	*expand_token(char *token);
static char	*expand_variable(char *token, size_t *i);

void	expand_tokens(t_app *app)
{
	size_t	i;

	i = 0;
	while (app->tokens[i])
	{
		app->tokens[i] = expand_token(app->tokens[i]);
		i++;
	}
}

static char	*expand_token(char *token)
{
	size_t	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			if (find_chr(token + i + 1, '\'') != -1)
				i = i + 1 + (size_t)find_chr(token + i + 1, '\'');
		if (token[i] == '$')
		{
			i++;
			token = expand_variable(token, &i);
		}
		i++;
	}
	token = delete_quotes(token);
	return (token);
}

static char	*expand_variable(char *token, size_t *i)
{
	size_t	j;
	char	*temp;
	char	*env;
	char	*new_token;

	j = *i;
	while (token[*i] && token[*i] != '\"' && token[*i] != '\''
		&& token[*i] != ' ' && token[*i] != '$')
		(*i)++;
	temp = str_range_cpy(token, j, *i);
	env = getenv(temp);
	new_token = str_insert(token, env, j - 1, *i - 1);
	*i = j;
	free(temp);
	free(token);
	return (new_token);
}
