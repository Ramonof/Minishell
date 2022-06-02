#include "minishell.h"

static char		*expand_token(char **envp, char *token);
static char		*expand_variable(char **envp, char *token, size_t *i);
static char		*get_var(char **envp, char *varname);
static size_t	find_var(char *var, char *varname);

void	expand_tokens(t_app *app)
{
	size_t	i;

	i = 0;
	while (app->tokens[i])
	{
		app->tokens[i] = expand_token(app->data->env, app->tokens[i]);
		i++;
	}
}

static char	*expand_token(char **envp, char *token)
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
			token = expand_variable(envp, token, &i);
		}
		i++;
	}
	token = delete_quotes(token);
	return (token);
}

static char	*expand_variable(char **envp, char *token, size_t *i)
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
	env = get_var(envp, temp);
	if (ft_strlen(temp) == 0)
		new_token = str_insert(token, "$", j - 1, *i - 1);
	else
		new_token = str_insert(token, env, j - 1, *i - 1);
	*i = j;
	free(temp);
	free(token);
	return (new_token);
}

static char	*get_var(char **envp, char *varname)
{
	int		i;
	char	*var;

	i = 0;
	while (envp[i])
	{
		if (find_var(envp[i], varname))
			break ;
		i++;
	}
	var = envp[i];
	i = find_chr(var, '=') + 1;
	return (var + i);
}

static size_t	find_var(char *var, char *varname)
{
	size_t	i;

	i = 0;
	while (varname[i] && var[i] != '=')
	{
		if (var[i] != varname[i])
			return (0);
		i++;
	}
	return (1);
}
