/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:38:04 by mrolande          #+#    #+#             */
/*   Updated: 2022/03/29 17:31:26 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, 0) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!command)
			return (NULL);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.tube[1], 1) < 0)
		msg_err("Dup2\n");
	close(pipex.tube[0]);
	if (dup2(pipex.infile, 0) < 0)
		msg_err("Dup2\n");
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (pipex.cmd_args && pipex.cmd_args[0])
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	else
		pipex.cmd = NULL;
	if (!pipex.cmd)
	{
		child_free(&pipex);
		ret_err("Command not found\n");
		exit(1);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) < 0)
	{
		child_free(&pipex);
		msg_err("Execve\n");
	}
}

void	second_child(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.tube[0], 0) < 0)
		msg_err("Dup2\n");
	close(pipex.tube[1]);
	if (dup2(pipex.outfile, 1) < 0)
		msg_err("Dup2\n");
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (pipex.cmd_args && pipex.cmd_args[0])
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	else
		pipex.cmd = NULL;
	if (!pipex.cmd)
	{
		child_free(&pipex);
		ret_err("Command not found\n");
		exit(1);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) < 0)
	{
		child_free(&pipex);
		msg_err("Execve\n");
	}
}
