/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:29:41 by mrolande          #+#    #+#             */
/*   Updated: 2022/05/22 11:29:41 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*find_home(char **envp)
// {
// 	while (ft_strncmp("HOME", *envp, 4))
// 		envp++;
// 	if (!*envp)
// 		return (NULL);
// 	return (*envp + 5);
// }

// void	handle_pwd(t_data *data)
// {
// 	ft_putstr(data->pwd);
// 	ft_putstr("\n");
// 	// g_status = 0;
// }

void	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	g_status = 0;
	free(cwd);
}

