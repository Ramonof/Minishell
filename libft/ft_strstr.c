/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:29:09 by mrolande          #+#    #+#             */
/*   Updated: 2022/05/29 12:29:09 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;

	len = ft_strlen(needle);
	if (!(*needle))
		return ((char *)haystack);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, len) != 0)
			haystack++;
		else
			return ((char *)haystack);
	}
	return (NULL);
}
