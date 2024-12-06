/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:49:26 by camurill          #+#    #+#             */
/*   Updated: 2024/01/20 22:58:59 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = ft_strlen(dst);
	len = ft_strlen(dst);
	while (src[i] != '\0' && (j < dstsize - 1) && dstsize > 0)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	if (len > dstsize)
		len = dstsize;
	return (len + ft_strlen(src));
}
