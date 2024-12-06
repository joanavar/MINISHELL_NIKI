/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 08:12:43 by camurill          #+#    #+#             */
/*   Updated: 2024/01/24 00:23:30 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	else if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s + start);
	if (i < len)
		len = i;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < len)
	{
		ptr[j] = s[start + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
