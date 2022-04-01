/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:32:04 by mrolande          #+#    #+#             */
/*   Updated: 2022/03/29 17:32:27 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void	sub_dup2(int zero, int first)
{
	if (dup2(zero, 0) < 0)
	{
		msg("dup2");
		exit(1);
	}
	if (dup2(first, 1) < 0)
	{
		msg("dup2");
		exit(1);
	}
}

void	child(t_pipex p, char **argv, char **envp)
{
	p.pid = fork();
	if (p.pid < 0)
		write(2, "fork", ft_strlen("fork"));
	if (!p.pid)
	{
		if (p.idx == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		p.cmd_args = ft_split(argv[2 + p.here_doc + p.idx], ' ');
		if (p.cmd_args && p.cmd_args[0])
			p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);
		else
			p.cmd = NULL;
		if (!p.cmd)
		{
			msg_pipe(p.cmd_args[0]);
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
}
