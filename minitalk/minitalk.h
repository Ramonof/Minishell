/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:07:35 by etobias           #+#    #+#             */
/*   Updated: 2022/02/21 16:09:28 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>

int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
int		ft_isspace(int c);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);

#endif
