/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 07:32:44 by camurill          #+#    #+#             */
/*   Updated: 2024/01/20 22:42:49 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	f;

	f = (char)c;
	ptr = 0;
	while (*s != '\0')
	{
		if (*s == f)
			ptr = (char *)s;
		s++;
	}
	if (*s == f)
		ptr = (char *)s;
	return (ptr);
}
