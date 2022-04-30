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

// int	my_execute(t_app app, char **envp)
// {
// 	//char	*cmd = "cat";
// 	//char	*cmd_arg = "cat ", "-m";
// 	// int		fd = open("Hello.txt",O_RDONLY);
// 	// char **cmd_args = ft_split(cmd, ' ');
// 	pid_t pid = fork();
// 	if (!pid)
// 	{
// 		printf("here %s\n", app.cmd_array[0].cmd);
// 		// int i = 0;
// 		// while (app.cmd_array[0].cmd_flags[i])
// 		// {
// 		// 	printf("here %s\n", app.cmd_array[0].cmd_flags[i]);
// 		// 	i++;
// 		// }

// 		dup2(0, 0);
// 		exec_cmd(app.cmd_array[0].cmd, app.cmd_array[0].cmd_args, envp);
// 	}
// 	waitpid(-1, NULL, 0);
// 	return (0);
// }

int	my_execute(t_app app, char **envp)
{
	t_pipex pipex;

	pipex.infile = 0;
	pipex.outfile = 1;
	pipex.pipe_nmbs = 2 * (app.cmd_number - 1);
	pipex.cmd_nmbs = app.cmd_number;
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nmbs);
	printf("%s\n", app.cmd_array[0].cmd_args[0]);
	if (!pipex.pipe)
		return (ret_err("Pipe"));
	creat_pipes(&pipex);

	pipex.idx = -1;
	while (++(pipex.idx) < app.cmd_number)
	{
		exec_cmd(pipex, app.cmd_array[pipex.idx], envp);
	}
	close_pipes(&pipex);
	while (pipex.idx--)
		waitpid(-1, NULL, 0);
	//parent_free(&pipex, 0);
	return (0);
}

int	start_my_execute(t_app app, char **envp)
{
	if (!ft_strncmp(app.cmd_array[0].cmd, "cd", 3))
		handle_cd(app.cmd_array[0]); //printf("here be cd\n");
	else
		return (my_execute(app, envp));
	return (1);
}
