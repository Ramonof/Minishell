/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:25:21 by etobias           #+#    #+#             */
/*   Updated: 2022/06/18 21:35:20 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_handling(void)
{
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
}

void	sig_quit(int code)
{
	code += 0;
	if (g_status.pid == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putchar_fd('\n', 1);
}

void	sig_int(int code)
{
	code += 0;
	if (g_status.pid == 0)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putchar_fd('\n', 1);
}
