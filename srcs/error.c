/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:25:54 by mrolande          #+#    #+#             */
/*   Updated: 2022/04/01 14:25:54 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *err)
{
	write(2, err, ft_strlen(err));
	exit(1);
}

void	msg_pipe(char *err)
{
	write(2, "Command not found: ", ft_strlen("Command not found: "));
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit(1);
}

void	errno_exit(char *err)
{
	perror(err);
	exit (errno);
}

void	perror_sentence(char *err, int status)
{
	g_status = status;
	perror(err);
}

int	ret_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

void	void_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

char	**ret_err_char(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (NULL);
}
