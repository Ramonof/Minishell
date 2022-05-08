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

// char	*find_path(char **envp)
// {
// 	while (ft_strncmp("PATH", *envp, 4))
// 		envp++;
// 	if (!*envp)
// 		return (NULL);
// 	return (*envp + 5);
// }

static void	sub_dup2(int zero, int first)
{
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
	//char *env_path;
	//char **cmd_paths;

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
		//env_path = find_path(envp);
		//cmd_paths = ft_split(env_path, ':');
		cmd_st.cmd = get_cmd(p.cmd_paths, cmd_st.cmd);
		if (execve(cmd_st.cmd, cmd_st.cmd_args, envp) < 0)
			printf("error: ");
		exit(1);
	}
}
