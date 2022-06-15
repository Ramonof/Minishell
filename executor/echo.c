/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:12:02 by mrolande          #+#    #+#             */
/*   Updated: 2022/06/08 00:31:40 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_echo(char **args, t_command cmd_st)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	g_status = 0;
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		n_flag = 1;
	while (args[i])
	{
		write(cmd_st.output_desc, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(cmd_st.output_desc, " ", 1);
		i++;
	}
	if (!n_flag)
		write(cmd_st.output_desc, "\n", 1);
}
