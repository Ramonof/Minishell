/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:55:21 by mrolande          #+#    #+#             */
/*   Updated: 2022/03/23 10:55:21 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

int	main(void)
{
	int	fd;
	char *line;

	// libft working
	printf("Hello LIBFT!\n");
	// *************
	// gnl working
	fd = open("Hello.txt",O_RDONLY);
	get_next_line(fd, &line, 0);
	printf("%s\n", line);
	close(fd);
	free(line);
	// *************
	// readline working
	line = readline(">> ");
	while (line)
	{
		if (strlen(line) > 0)
		{
			add_history(line);
    	}
		if (line)
		{
			printf("%s\n", line);
			free(line);
		}
		line = readline(">> ");
  	}
	// ************* (183)
	return (0);
}
