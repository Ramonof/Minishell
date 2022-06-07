/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:21 by etobias           #+#    #+#             */
/*   Updated: 2022/06/08 00:25:22 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit(int code)
{
	code += 0;
}

void	sig_int(int code)
{
	ft_putstr_fd("\n>> ", 1);
	code += 0;
}
