/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:36:51 by mrolande          #+#    #+#             */
/*   Updated: 2022/02/04 15:36:51 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

int	ret_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

void	msg_err(char *err)
{
	perror(err);
	exit (1);
}
