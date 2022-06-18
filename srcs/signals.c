/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:21 by etobias           #+#    #+#             */
/*   Updated: 2022/06/18 14:21:10 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_handling(void)
{
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
}

void	reset_signal_handling(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	sig_quit(int code)
{
	code += 0;
	printf(">> ");
}

void	sig_int(int code)
{
	ft_putstr_fd("\n>> ", 1);
	code += 0;
}
