/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:36:40 by mrolande          #+#    #+#             */
/*   Updated: 2022/02/09 16:46:45 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_free(t_pipex *pipex, char *err)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
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
	if (err)
		msg_err(err);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
	}
	if (pipex->cmd_args)
		free(pipex->cmd_args);
	if (pipex->cmd)
		free(pipex->cmd);
}
