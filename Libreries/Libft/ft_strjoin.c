/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:12:21 by camurill          #+#    #+#             */
/*   Updated: 2024/01/23 18:46:03 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	k = ft_strlen(s2);
	j = 0;
	s3 = (char *)malloc(sizeof(char) * (i + k + 1));
	if (!s3)
		return (0);
	while (i-- > 0)
	{
		s3[j] = s1[j];
		j++;
	}
	i = 0;
	while (k-- > 0)
		s3[j++] = s2[i++];
	s3[j] = '\0';
	return (s3);
}
