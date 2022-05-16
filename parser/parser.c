#include "minishell.h"

static void	get_tokens(t_app *app);
static char	*get_next_token(char *str, size_t *i);
static void	skip_quotes(char *str, size_t *i);
static void	free_tokens(t_app *app);
static int	find_redirection(char *str, size_t *i, size_t j);
static void	expand_tokens(t_app *app);
static char	*expand_token(t_app *app, char *token);
static char	*expand_variable(char *token, size_t *i);
static char	*delete_quotes(char *token);
static char	*str_remove_char(char *str, char to_delete);

void	start_parser(t_app *app)
{
	app->tokens = NULL;
	get_tokens(app);
	expand_tokens(app);
	for (int i = 0; app->tokens[i]; i++)
		printf("token: %s\n", app->tokens[i]);
	free_tokens(app);
}

static void	get_tokens(t_app *app)
{
	char	*token;
	size_t	i;

	i = 0;
	while (app->line[i])
	{
		token = get_next_token(app->line, &i);
		app->tokens = array_add(app->tokens, token);
		free(token);
	}
}

static char	*get_next_token(char *str, size_t *i)
{
	char	*token;
	size_t	j;

	while (str[*i] && str[*i] == ' ')
		(*i)++;
	j = *i;
	while (str[*i] && str[*i] != ' ')
	{
		skip_quotes(str, i);
		if (find_redirection(str, i, j))
			break ;
		(*i)++;
	}
	token = str_range_cpy(str, j, *i);
	return (token);
}

static void	skip_quotes(char *str, size_t *i)
{
	if (str[*i] == '\'')
	{
		if (find_chr(str + *i + 1, '\'') != -1)
			*i = *i + 1 + (size_t)find_chr(str + *i + 1, '\'');
	}
	if (str[*i] == '\"')
		if (find_chr(str + *i + 1, '\"') != -1)
			*i = *i + 1 + (size_t)find_chr(str + *i + 1, '\"');
}

static void	free_tokens(t_app *app)
{
	size_t	i;

	if (!app->tokens)
		return ;
	i = 0;
	while (app->tokens[i])
		free(app->tokens[i++]);
	free(app->tokens);
	app->tokens = NULL;
}

static int	find_redirection(char *str, size_t *i, size_t j)
{
	if (str[*i] == '>')
	{
		if (*i != j)
			return (1);
		while (str[*i] == '>')
			(*i)++;
		return (1);
	}
	if (str[*i] == '<')
	{
		if (*i != j)
			return (1);
		while (str[*i] == '<')
			(*i)++;
		return (1);
	}
	return (0);
}

static void	expand_tokens(t_app *app)
{
	size_t	i;

	i = 0;
	while (app->tokens[i])
	{
		app->tokens[i] = expand_token(app, app->tokens[i]);
		i++;
	}
}

static char	*expand_token(t_app *app, char *token)
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
