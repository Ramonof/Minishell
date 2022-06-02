#include "minishell.h"

static void	check_redirects(char **tokens);
static void	check_next_token(char *token);

void	check_tokens(t_app *app)
{
	check_redirects(app->tokens);
}

static void	check_redirects(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], "<<")
				|| !ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
			{
				check_next_token(tokens[i + 1]);
			}
			else
				error_exit("error: unexpected symbol\n");
		}
		else if (tokens[i][0] == '|')
		{
			if (!ft_strcmp(tokens[i], "|"))
				check_next_token(tokens[i + 1]);
			else
				error_exit("error: unexpected symbol\n");
		}
		i++;
	}
}

static void	check_next_token(char *token)
{
	if (!token)
		error_exit("error: expected redirect/pipe file\n");
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, "<<")
		|| !ft_strcmp(token, ">") || !ft_strcmp(token, ">>"))
	{
		error_exit("error: unexpected symbol\n");
	}
	if (!ft_strcmp(token, "|"))
		error_exit("error: unexpected symbol\n");
}
