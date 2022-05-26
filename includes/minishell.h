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
}	t_data;

typedef struct	s_command
{
	char	**args;			// массив аргументов
	int		input_desc;		// входной дескриптор
	int		output_desc;	// выходной дескриптор
}	t_command;

typedef struct s_app
{
	char		*line;				// прочтённая строка
	char		**tokens;			// массив отдельных токенов
	t_command	**cmds;				// массив указателей на команды
	int			cmd_number;			// число команд
	int			pipe_number;		// число пайпов
	int			last_cmd_result;	// код завершения последней команды
}	t_app;

/* executor.c */
int		start_my_execute(t_app app, char **envp);
int		my_execute(t_app app, char **envp);
void	exec_cmd(t_pipex p, char **cmd_st, char **envp);
void	close_pipes(t_pipex *pipex);

/* cd */
void	handle_cd(char **cmd_st, char **envp);

/* tokens_check.c */
void	tokens_check(char **tokens);

/* error.c */
void	errno_exit(char *err);
void	msg_pipe(char *err);
void	error_exit(char *err);
int		ret_err(char *msg);

/* strcmp.c */
int	ft_strcmp(const char *str1, const char *str2);

/* parser.c */
void	start_parser(t_app *app);
void	free_cmds(t_app *app);

/* parser_utils.c */
size_t	array_len(char **array);
char	*str_range_cpy(char *str, size_t start, size_t end);
int		find_chr(const char *s, int c);
char	*str_insert(char *str, char *to_insert, size_t start, size_t end);

/* get_tokens.c */
void	get_tokens(t_app *app);

/* expand_tokens.c */
void	expand_tokens(t_app *app);

/* alloc_cmds.c */
void	alloc_cmds(t_app *app);
void	get_cmds(t_app *app);

/* delete_quotes.c */
char	*delete_quotes(char *token);

/* array_operations.c */
char	**array_add(char **array, char *str);
char    **array_remove(char **array, size_t index);

/* handle_redirects.c */
void	handle_redirects(t_app *app, size_t *i, size_t cmd_i);

#endif