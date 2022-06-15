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
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include <sys/types.h>
# include <sys/wait.h>

# define MALLOC_ERROR "Error : Malloc returned NULL\n"
# define MALLOC_ERROR_CODE 1
# define PIPE_ERROR "Error : Pipe\n"
# define SYNTAX_ERROR_CODE 2
# define NO_FILE_MENTIONED_ERROR "Error: no file after redirect/pipe\n"
# define UNEXPECTED_SYMBOL_ERROR "Error: unexpected symbol\n"
# define UNCLOSED_QUOTES_ERROR "Error: unclosed quotes\n"

# define HEREDOC ".heredoc_tmp"

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
	t_data		*data;
}	t_app;

extern int		g_status;

/* init_env.c */
char	**init_env(char **envp);

/* executor.c */
void	start_my_execute(t_app app, char **envp, t_data *data);
void	my_execute(t_app app, char **envp);
void	exec_cmd(t_pipex p, t_command cmd_st, char **envp);
void	handle_exec(t_pipex p, t_command cmd_st, char **envp);
void	close_pipes(t_pipex *pipex);

/* cd */
void	handle_cd(char **args, t_data *data);
int		change_pwd(t_data *data, char *input);

/* handle_unset.c */
void	handle_unset(char **inputs, t_data *data);
char	**unset_env(char **old_env, int index);

/* export.c */
void	handle_export(char **inputs, t_data *data);
void	export_alone(t_data *data);
char	**export_env(char **old_env, char *export);
void	replace_var(char *new_var, t_data *data, int index);
int		var_index(char *name, t_data *data);

/* export_utils.c */
int		check_export(char *str);
int		print_export(char **env);

/* env.c */
void	free_env(char **env);
int		envlen(char **env);
char	**dup_env(char **env);
void	handle_env(char **env, t_command cmd_st);

/* pwd.c */
void	handle_pwd(t_command cmd_st);

/* echo.c */
void	handle_echo(char **args, t_command cmd_st);

/* exit.c */
void	error_sentence(char *str, int status);
void	handle_exit(char **inputs, t_data *data);

/* tokens_check.c */
void	tokens_check(char **tokens);

/* error.c */
void	errno_exit(char *err);
void	msg_pipe(char *err);
void	error_exit(char *err);
int		ret_err(char *msg);
char	**ret_err_char(char *msg);
void	void_err(char *msg);
void	perror_sentence(char *err, int status);

/* strcmp.c */
int	ft_strcmp(const char *str1, const char *str2);

/* parser.c */
int	start_parser(t_app *app);
void	free_cmds(t_app *app);
void	free_tokens(t_app *app);

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
void	handle_redirects(t_app *app, size_t i, size_t cmd_i);

/* syntax_checker.c */
int	start_syntax_checker(t_app *app);

/* check_line.c */
int	check_line(char *line);

/* check_tokens.c */
int	check_tokens(t_app *app);

/* signals.c */
void	sig_quit(int code);
void	sig_int(int code);

#endif