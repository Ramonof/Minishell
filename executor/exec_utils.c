/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:36:00 by mrolande          #+#    #+#             */
/*   Updated: 2022/06/15 21:36:00 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_paths)
	{
		while (pipex->cmd_paths[i])
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
	}
	if (pipex->cmd_paths)
		free(pipex->cmd_paths);
	if (pipex->pipe)
		free(pipex->pipe);
}

char	*find_path(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

void	init_p(int *status, t_pipex	*pipex, t_app app)
{
	*status = 0;
	(*pipex).infile = app.cmds[0][0].input_desc;
	(*pipex).outfile = app.cmds[app.cmd_number - 1][0].output_desc;
	(*pipex).pipe_nmbs = 2 * (app.cmd_number - 1);
	(*pipex).cmd_nmbs = app.cmd_number;
}
