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

// static void	sub_dup2(int zero, int first)
// {
// 	if (dup2(zero, 0) < 0)
// 	{
// 		printf("exit\n");
// 		error_exit("dup2");
// 		exit(1);
// 	}
// 	if (dup2(first, 1) < 0)
// 	{
// 		printf("exit\n");
// 		error_exit("dup2");
// 		exit(1);
// 	}
// }

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

void	exec_cmd(t_pipex p, t_command cmd_st, char **envp)
{
	char *cmd_full;

	p.pid = fork();
	if (p.pid < 0)
		write(2, "fork", ft_strlen("fork"));
	if (!p.pid)
	{
		// if (p.idx == 0)
		// 	sub_dup2(p.infile, p.pipe[1]);
		// else if (p.idx == p.cmd_nmbs - 1)
		// 	sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		// else
		// 	sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		if (p.idx == 0)
			sub_dup2(cmd_st, p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
			sub_dup2(cmd_st, p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(cmd_st, p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		cmd_full = get_cmd(p.cmd_paths, cmd_st.args[0]);
		if (execve(cmd_full, cmd_st.args, envp) < 0)
			ft_putstr_fd("error: exec", 2);
		exit(1);
	}
}
