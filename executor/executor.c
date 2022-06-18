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

static int	creat_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
		{
			perror_sentence("PIPE", errno);
			return (1);
		}
		i++;
	}
	return (0);
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

void	handle_exec_type(t_pipex p, t_command cmd_st, char **envp)
{
	if (!ft_strncmp(cmd_st.args[0], "env", 4))
		handle_env(envp, cmd_st);
	else if (!ft_strncmp(cmd_st.args[0], "echo", 5))
		handle_echo(cmd_st.args, cmd_st);
	else if (!ft_strncmp(cmd_st.args[0], "pwd", 4))
		handle_pwd(cmd_st);
	else if (!ft_strncmp(cmd_st.args[0], "cd", 3))
		exit(0);
	else if (!ft_strncmp(cmd_st.args[0], "unset", 6))
		exit(0);
	else if (!ft_strncmp(cmd_st.args[0], "export", 7))
		exit(0);
	else if (!ft_strncmp(cmd_st.args[0], "exit", 5))
		exit(0);
	else
		exec_cmd(p, cmd_st, envp);
}

void	my_execute(t_app app, char **envp)
{
	t_pipex	pipex;
	int		code;

	init_p(&code, &pipex, app);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nmbs);
	pipex.env_path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');
	if ((!pipex.cmd_paths && find_path(envp)) || !pipex.pipe)
		error_sentence(MALLOC_ERROR, MALLOC_ERROR_CODE);
	if (!pipex.pipe)
		return ;
	if (creat_pipes(&pipex))
		return (parent_free(&pipex));
	pipex.idx = -1;
	while (++(pipex.idx) < app.cmd_number)
	{
		handle_exec(pipex, app.cmds[pipex.idx][0], envp);
	}
	close_pipes(&pipex);
	while (pipex.idx--)
		waitpid(-1, &code, 0);
	g_status.pid = 0;
	g_status.exit_code = WEXITSTATUS(code);
	parent_free(&pipex);
}

void	start_my_execute(t_app app, char **envp, t_data *data)
{
	if (app.cmd_number - 1)
		my_execute(app, envp);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "cd", 3))
		handle_cd(app.cmds[0][0].args, data);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "unset", 6))
		handle_unset(app.cmds[0][0].args, data);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "export", 7))
		handle_export(app.cmds[0][0].args, data);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "env", 4))
		handle_env(envp, app.cmds[0][0]);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "exit", 5))
		handle_exit(app.cmds[0][0].args, data);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "echo", 5))
		handle_echo(app.cmds[0][0].args, app.cmds[0][0]);
	else if (!ft_strncmp(app.cmds[0][0].args[0], "pwd", 4))
		handle_pwd(app.cmds[0][0]);
	else
		my_execute(app, envp);
}
