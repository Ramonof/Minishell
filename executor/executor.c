/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:40:02 by mrolande          #+#    #+#             */
/*   Updated: 2022/04/01 13:40:02 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_execute(char *cmd, char **envp)
{
	//char	*cmd = "cat";
	//char	*cmd_arg = "cat ", "-m";
	int		fd = open("Hello.txt",O_RDONLY);
	char **cmd_args = ft_split(cmd, ' ');
	pid_t pid = fork();
	if (!pid)
	{
		dup2(fd, 0);
		exec_cmd(cmd_args[0], cmd_args, envp);
	}
	waitpid(-1, NULL, 0);
	return (0);
}