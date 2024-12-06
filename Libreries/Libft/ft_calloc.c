/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 05:34:28 by camurill          #+#    #+#             */
/*   Updated: 2024/01/17 21:18:47 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len);

void	*ft_calloc(size_t count, size_t size)
{
	size_t	max_size;
	int		i;
	void	*ptr;

	i = 0;
	max_size = count * size;
	ptr = malloc(max_size);
	if (((unsigned char *)ptr) != NULL)
	{
		ft_memset(ptr, 0, max_size);
		i++;
	}
	return (ptr);
}
