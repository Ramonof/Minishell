/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:12:23 by mrolande          #+#    #+#             */
/*   Updated: 2022/02/02 19:12:23 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "../gnl/get_next_line.h"

typedef struct s_pipex
{
	int		cmd_nmbs;
	int		pipe_nmbs;
	char	*env_path;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		here_doc;
	pid_t	pid;
	int		infile;
	int		outfile;
	int		*pipe;
	int		idx;
}	t_pipex;

void	close_pipes(t_pipex *pipex);

void	child(t_pipex pipex, char **argv, char **envp);

void	parent_free(t_pipex *pipex, int mode);
void	child_free(t_pipex *pipex);
void	pipe_free(t_pipex *pipex);

char	*find_path(char **envp);
void	get_infile(char **argv, t_pipex *pipex);
void	get_outfile(char *argv, t_pipex *pipex);

int		args_in(char *arg, t_pipex *pipex);
void	here_doc(char *argv, t_pipex *pipex, int file);

void	msg_error(char *err);
void	msg_pipe(char *arg);
int		msg(char *err);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
