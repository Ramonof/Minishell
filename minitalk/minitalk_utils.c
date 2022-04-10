/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:07:24 by etobias           #+#    #+#             */
/*   Updated: 2022/02/21 16:09:18 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;
	char	c;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	if (n / 10)
		ft_putnbr_fd(n / 10 * sign, fd);
	c = '0' + n % 10 * sign;
	write(fd, &c, 1);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	number;

	sign = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\n'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	return (number * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	string_length;

	string_length = 0;
	while (str[string_length])
		string_length++;
	return (string_length);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	length;

	if (fd < 0 || s == NULL)
		return ;
	length = ft_strlen(s);
	write(fd, s, length);
}
