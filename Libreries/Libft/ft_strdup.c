/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 06:22:10 by camurill          #+#    #+#             */
/*   Updated: 2024/01/21 17:02:42 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *s1)
{
	unsigned int	len;
	char			*str;

	len = (unsigned int)ft_strlen(s1);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	else
		ft_memcpy(str, (char *)s1, len + 1);
	return (str);
}
