/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:42:09 by camurill          #+#    #+#             */
/*   Updated: 2024/01/25 21:14:08 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*test;
	unsigned int	init;
	unsigned int	final;
	unsigned int	i;

	if (!s1 || !set)
		return (0);
	init = 0;
	final = ft_strlen(s1);
	while (s1[init] && ft_strchr(set, s1[init]))
		init++;
	while (final > init && ft_strchr(set, s1[final]))
		final--;
	i = final - init + 1;
	if (*set == '\0')
		i = final + 1;
	test = ft_substr((char *)s1, init, i);
	return (test);
}
