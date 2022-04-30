/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:44:36 by mrolande          #+#    #+#             */
/*   Updated: 2022/04/30 09:44:36 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cd(t_command cmd_st)
{
	if (chdir(cmd_st.cmd_args[1]) != 0)
		perror(cmd_st.cmd_args[1]);
	printf("good?\n");
}
