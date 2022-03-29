/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 00:13:03 by mrolande          #+#    #+#             */
/*   Updated: 2022/02/06 00:13:03 by mrolande         ###   ########.fr       */
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
	}
	free(buf);
	*line = get_line(rem);
	rem = trim_rem(rem);
	if (rd == 0 && !rem)
		return (0);
	return (1);
}
