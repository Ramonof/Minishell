/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:07:19 by etobias           #+#    #+#             */
/*   Updated: 2022/02/21 16:13:50 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_args(int argc, char **argv);
static int	is_number(char *str);
static int	send_message(int pid, char *str);

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (check_args(argc, argv))
		return (1);
	pid = ft_atoi(argv[1]);
	str = argv[2];
	if (!send_message(pid, str))
	{
		ft_putstr_fd("Error: Wrong PID\n", 1);
		return (1);
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr_fd("Enter PID and message\n", 1);
		return (1);
	}
	if (argc == 2)
	{
		ft_putstr_fd("Enter message\n", 1);
		return (1);
	}
	if (!is_number(argv[1]))
	{
		ft_putstr_fd("PID is not a number\n", 1);
		return (1);
	}
	return (0);
}

static int	is_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	send_message(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					return (0);
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					return (0);
			}
			usleep(100);
		}
	}
	return (1);
}
