/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_comp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:37:14 by etobias           #+#    #+#             */
/*   Updated: 2022/06/16 16:37:15 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_comp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (-1);
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
