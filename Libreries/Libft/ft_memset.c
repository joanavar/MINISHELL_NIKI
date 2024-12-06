/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 05:48:39 by camurill          #+#    #+#             */
/*   Updated: 2024/01/20 20:47:20 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*str;
	unsigned char	f;

	i = 0;
	f = (unsigned char)c;
	str = (char *)b;
	while (i < len)
	{
		str[i] = f;
		i++;
	}
	return (str);
}
