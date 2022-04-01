/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:07:38 by etobias           #+#    #+#             */
/*   Updated: 2022/02/21 16:04:30 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int sig, siginfo_t *info, void *context);

int	main(void)
{
	struct sigaction	action;

	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int				i;
	static unsigned char	c;

	info += 0;
	context += 0;
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		write(1, &c, 1);
		c = 0;
		return ;
	}
	c <<= 1;
}
