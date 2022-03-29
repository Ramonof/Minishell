/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:12:21 by mrolande          #+#    #+#             */
/*   Updated: 2022/02/02 19:12:21 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (ft_strncmp("PATH", *envp, 4) < 0)
		return (NULL);
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main_check(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (ret_err("Wrong number of arguments\n"));
	if (!argv || !envp)
		return (ret_err("Environment\n"));
	pipex->paths = find_path(envp);
	if (!(pipex->paths))
		return (ret_err("Environment\n"));
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		msg_err("Infile");
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->outfile < 0)
		msg_err("Outfile");
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	if (!(pipex->cmd_paths))
	{
		close(pipex->infile);
		close(pipex->outfile);
		return (ret_err("Split failed to allocate memory\n"));
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (main_check(&pipex, argc, argv, envp))
		return (1);
	if (pipe(pipex.tube) < 0)
		parent_free(&pipex, "Pipe");
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		parent_free(&pipex, "Fork");
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		parent_free(&pipex, "Fork");
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex, NULL);
	return (0);
}
