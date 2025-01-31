/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 05:34:28 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 15:39:55 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len);

void	*ft_calloc(size_t count, size_t size)
{
	size_t	max_size;
	void	*ptr;

	max_size = count * size;
	ptr = malloc(max_size);
	if (((unsigned char *)ptr) != NULL)
		ft_memset(ptr, 0, max_size);
	return (ptr);
}
