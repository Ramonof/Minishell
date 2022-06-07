/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:50:07 by mrolande          #+#    #+#             */
/*   Updated: 2022/04/01 14:50:07 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, 0) == 0)
		return (cmd);
	if (!paths)
		return (NULL);
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

static void	sub_dup2(t_command cmd_st, int zero, int first)
{
	if (cmd_st.input_desc != 0)
		zero = cmd_st.input_desc;
	if (cmd_st.output_desc != 1)
		first = cmd_st.output_desc;
	if (dup2(zero, 0) < 0)
	{
		printf("exit\n");
		error_exit("dup2");
		exit(1);
	}
	if (dup2(first, 1) < 0)
	{
		printf("exit\n");
		error_exit("dup2");
		exit(1);
	}
}

void	handle_exec(t_pipex p, t_command cmd_st, char **envp)
{
	// int		status = 0;

	p.pid = fork();
	if (p.pid < 0)
		write(2, "fork", ft_strlen("fork"));
	if (!p.pid)
	{
		if (p.pipe_nmbs == 0)
			sub_dup2(cmd_st, 0, 1);
		else if (p.idx == 0)
			sub_dup2(cmd_st, p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
			sub_dup2(cmd_st, p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(cmd_st, p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		if (!ft_strncmp(cmd_st.args[0], "env", 4))
			handle_env(envp);
		else if (!ft_strncmp(cmd_st.args[0], "echo", 5))
			handle_echo(cmd_st.args);
		else if (!ft_strncmp(cmd_st.args[0], "pwd", 4))
			handle_pwd();
		else
			exec_cmd(p, cmd_st, envp);
		exit(g_status);
	}
	// else
	// 	waitpid(p.pid, &status, 0);
	// g_status = WEXITSTATUS(status);
}

void	exec_cmd(t_pipex p, t_command cmd_st, char **envp)
{
	char	*cmd_full;

	// if (p.idx == 0)
	// 	sub_dup2(p.infile, p.pipe[1]);
	// else if (p.idx == p.cmd_nmbs - 1)
	// 	sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
	// else
	// 	sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
	cmd_full = get_cmd(p.cmd_paths, cmd_st.args[0]);
	if (!cmd_full)
		errno_exit(cmd_st.args[0]);
	if (execve(cmd_full, cmd_st.args, envp) < 0)
		perror(cmd_st.args[0]);
	exit(errno);
}
