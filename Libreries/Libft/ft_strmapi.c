/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:58:29 by camurill          #+#    #+#             */
/*   Updated: 2024/01/23 17:42:00 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*full;
	unsigned int	i;

	if (!s)
		return (0);
	full = (char *)malloc(ft_strlen(s) + 1);
	if (!full)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		full[i] = f(i, s[i]);
		i++;
	}
	full[i] = '\0';
	return (full);
}
