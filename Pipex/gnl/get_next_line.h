/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:13:57 by mrolande          #+#    #+#             */
/*   Updated: 2022/02/05 23:32:29 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

int		get_next_line(int fd, char **line, int mode);
size_t	ft_strlen(const char *s);
int		find_nl(char *str);
char	*str_join(char *s1, char *s2);
char	*get_line(char *str);
char	*trim_rem(char *str);
int		some_error(char *str);

#endif
