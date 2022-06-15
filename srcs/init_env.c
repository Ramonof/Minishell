/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:29:47 by mrolande          #+#    #+#             */
/*   Updated: 2022/06/08 00:36:42 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_pwd(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp && ft_strncmp("PWD=", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 4);
}

int	fill_envpd2(char **envp, char **envpd)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			j++;
		}
		envpd[i] = (char *)malloc(sizeof(char) * (j + 1));
		if (!envpd[i])
			return (ret_err("malc"));
		j = 0;
		while (envp[i][j])
		{
			envpd[i][j] = envp[i][j];
			j++;
		}
		envpd[i][j] = envp[i][j];
		i++;
	}
	envpd[i] = envp[i];
	return (0);
}

char	**fill_envpd(char **envp)
{
	int		i;
	char	**envpd;

	i = 0;
	while (envp[i])
		i++;
	envpd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envpd)
		return (ret_err_char("malc"));
	if (fill_envpd2(envp, envpd))
		return (ret_err_char("malc"));
	return (envpd);
}

void	print_envp(char **envpd)
{
	int	i;

	i = 0;
	while (envpd[i])
	{
		printf("%s\n", envpd[i]);
		i++;
	}
}

char	**init_env(char **envp)
{
	char	**envpd;

	envpd = fill_envpd(envp);
	if (!envpd)
		return (ret_err_char("malloc"));
	return (envpd);
}
