/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:37:06 by camurill          #+#    #+#             */
/*   Updated: 2024/01/20 20:53:07 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	if (!p2 && n > 0 && !p1)
		return (0);
	while (i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	return (p1);
}
