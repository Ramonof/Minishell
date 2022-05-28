/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:44:36 by mrolande          #+#    #+#             */
/*   Updated: 2022/04/30 09:44:36 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(char **envp)
{
	while (ft_strncmp("HOME", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

void	handle_cd(t_command cmd_st, char **envp)
{
	char	*homedir;

	if (!cmd_st.args[1])
	{
		homedir = find_home(envp);
		chdir(homedir);
	}
	else if (chdir(cmd_st.args[1]) != 0)
		perror(cmd_st.args[1]);
	printf("good?\n");
}
