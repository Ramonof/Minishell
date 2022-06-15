/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:47:09 by mrolande          #+#    #+#             */
/*   Updated: 2022/06/15 21:47:09 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

char	**ret_err_char(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (NULL);
}
