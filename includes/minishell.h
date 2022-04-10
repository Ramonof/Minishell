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
}	t_cmd;

typedef struct s_command
{
	char	*cmd;
	char	**cmd_args;
	char	**cmd_flags;
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
int		my_execute(char *cmd, char **envp);
void	exec_cmd(char *cmd, char **cmd_arg, char **envp);

/* parser.c */
void	fill_commands_array(t_app *app);

/* alloc.c */
void	alloc_commands(t_app *app);
void	alloc_flags(t_app *app, size_t cmd_i, size_t end_i, size_t cmd_ind);
void	alloc_args(t_app *app, size_t cmd_i, size_t end_i, size_t cmd_ind);


#endif