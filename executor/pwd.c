/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:29:41 by mrolande          #+#    #+#             */
/*   Updated: 2022/06/08 00:34:13 by etobias          ###   ########.fr       */
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

void	handle_pwd(t_command cmd_st)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, cmd_st.output_desc);
	ft_putstr_fd("\n", cmd_st.output_desc);
	g_status = 0;
	free(cwd);
}
