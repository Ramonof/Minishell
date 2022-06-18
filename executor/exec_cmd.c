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
	g_status.pid = fork();
	if (g_status.pid < 0)
		perror(cmd_st.args[0]);
	if (!g_status.pid)
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
		handle_exec_type(p, cmd_st, envp);
		exit(g_status.exit_code);
	}
}

void	exec_cmd(t_pipex p, t_command cmd_st, char **envp)
{
	char	*cmd_full;

	cmd_full = get_cmd(p.cmd_paths, cmd_st.args[0]);
	if (cmd_full)
		execve(cmd_full, cmd_st.args, envp);
	errno_exit(cmd_st.args[0]);
}
