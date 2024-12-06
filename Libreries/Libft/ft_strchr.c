/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 07:22:42 by camurill          #+#    #+#             */
/*   Updated: 2024/01/20 21:23:58 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	f;

	i = 0;
	f = (char)c;
	while (s[i] && f != s[i])
		i++;
	if (s[i] == f)
		return ((char *)s + i);
	return (0);
}
