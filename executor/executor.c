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

static void	creat_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			ret_err("Pipe"); //parent_free(pipex, 1);
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nmbs))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

void	parent_free(t_pipex *pipex, int mode)
{
	int	i;

	i = 0;
	// close(pipex->infile);
	// close(pipex->outfile);
	// if (pipex->here_doc)
	// 	unlink(".heredoc_tmp");
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	free(pipex->pipe);
	if (mode == 1)
	{
		// msg_error("Pipe");
		printf("Pipe");
		exit(1);
	}
}

int	my_execute(t_app app, char **envp)
{
	t_pipex pipex;

	pipex.infile = app.cmds[0][0].input_desc;
	pipex.outfile = app.cmds[app.cmd_number-1][0].output_desc;
	pipex.pipe_nmbs = 2 * (app.cmd_number - 1);
	pipex.cmd_nmbs = app.cmd_number;
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nmbs);
	pipex.env_path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');
	if (!pipex.cmd_paths || !pipex.pipe)
		return (ret_err("malc")); //pipe_free(&pipex);
	if (!pipex.pipe)
		return (ret_err("Pipe"));
	creat_pipes(&pipex);

	pipex.idx = -1;
	while (++(pipex.idx) < app.cmd_number)
	{
		exec_cmd(pipex, app.cmds[pipex.idx][0], envp);
	}
	close_pipes(&pipex);
	while (pipex.idx--)
		waitpid(-1, NULL, 0);
	parent_free(&pipex, 0);
	return (0);
}

int	start_my_execute(t_app app, char **envp)
{
	if (!ft_strncmp(app.cmds[0][0].args[0], "cd", 3))
		handle_cd(app.cmds[0][0], envp);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "test", 5))
		printf("memory test\n");
	else
		return (my_execute(app, envp));
	return (1);
}
