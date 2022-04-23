/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:08:41 by mrolande          #+#    #+#             */
/*   Updated: 2022/04/01 15:13:20 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int		cmd_nmbs;       // Количество комманд
	int		pipe_nmbs;      // Количество труб
	char	*env_path;      // Константа PATH
	char	**cmd_paths;    // Константа PATH, разделенная
	char	*cmd;           // Команда
	char	**cmd_args;     // Флажки
	int		here_doc;       // Флажок <<
	pid_t	pid;            // Для каждого процесса свой
	int		infile;         // Вход файл удар
	int		outfile;        // Выход файл удар
	int		*pipe;          // Массив дескрипторов связаных функцией pipe
	int		idx;            // Номер процесса
}	t_pipex;

typedef	struct	s_data
{
	char		**env;
	int			fd_in;
	int			fd_out;
	char		*pwd;
}				t_data;

typedef struct s_command
{
	char	*cmd;
	char	**cmd_args;
	char	*input_file;
	char	*output_file;
}	t_command;

typedef struct s_app
{
	char		*line;
	char		**tokens;
	int			cmd_number;
	int			pipe_number;
	t_command	*cmd_array;
}	t_app;

/* executor.c */
int		my_execute(t_app app, char **envp);
void	exec_cmd(t_pipex p, t_command cmd_st, char **envp);
void	close_pipes(t_pipex *pipex);

/* parser.c */
void	fill_commands_array(t_app *app);

/* alloc.c */
void	alloc_commands(t_app *app);
void	alloc_args(t_app *app, size_t cmd_i, size_t end_i, size_t cmd_ind);

/* tokens_check.c */
void	tokens_check(char **tokens);

/* error.c */
void	errno_exit(char *err);
void	msg_pipe(char *err);
void	error_exit(char *err);
int		ret_err(char *msg);

/* strcmp.c */
int	ft_strcmp(const char *str1, const char *str2);

#endif