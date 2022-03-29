/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:25:55 by mrolande          #+#    #+#             */
/*   Updated: 2022/03/23 11:18:54 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	static_free(int mode, char *rem)
{
	if (mode != 1)
		return (-1);
	if (rem)
		free(rem);
	return (0);
}

int	some_error(char *str)
{
	if (str)
		free(str);
	return (-1);
}

int	big_error(char *str, char *rem)
{
	if (str)
		free(str);
	if (rem)
		free(rem);
	return (-1);
}

int	my_return(char *rem, int rd)
{
	if (rd == 0 && !rem)
		return (0);
	return (1);
}

/* 0 - default mode */
int	get_next_line(int fd, char **line, int mode)
{
	char		*buf;
	int			rd;
	static char	*rem;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || mode == 1)
		return (static_free(mode, rem));
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (some_error(rem));
	rd = 1;
	while (!find_nl(rem) && rd > 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
			return (some_error(buf));
		buf[rd] = '\0';
		rem = str_join(rem, buf);
		if (!rem)
			return (big_error(buf, rem));
	}
	*line = get_line(rem, buf);
	if (!*line)
		return (big_error(NULL, rem));
	rem = trim_rem(rem);
	return (my_return(rem, rd));
}
