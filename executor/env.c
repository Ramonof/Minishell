/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:22:31 by mrolande          #+#    #+#             */
/*   Updated: 2022/06/02 12:20:10 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = envlen(env);
	while (i < env_len)
		free(env[i++]);
	free(env);
}

int		envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

char	**dup_env(char **env)
{
	char	**data_env;
	int		i;

	i = 0;
	data_env = malloc(sizeof(char *) * envlen(env));
	if (!data_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = 0;
	return (data_env);
}

void	handle_env(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		str = ft_strstr(env[i], "=");
		if (str)
		{
			j = 0;
			while (env[i][j])
			{
				write(1, &env[i][j], 1);
				j++;
			}
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	g_status = 0;
}
