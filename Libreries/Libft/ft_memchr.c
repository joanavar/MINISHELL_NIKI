/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:59:06 by camurill          #+#    #+#             */
/*   Updated: 2024/01/20 22:06:12 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	f;

	i = 0;
	f = (unsigned char)c;
	str = (unsigned char *)s;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str[i] == f)
			return (str + i);
		i++;
	}
	return (NULL);
}
