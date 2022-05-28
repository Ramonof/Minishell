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

void	handle_pwd(t_data *data)
{
	ft_putstr(data->pwd);
	ft_putstr("\n");
}

