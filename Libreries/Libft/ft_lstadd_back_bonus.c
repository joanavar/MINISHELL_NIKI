/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:28:44 by camurill          #+#    #+#             */
/*   Updated: 2024/03/08 14:13:45 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//corregir este con main
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buffer;

	buffer = (*lst);
	if (*lst)
	{
		while (buffer->next != 0)
			buffer = buffer->next;
		buffer->next = new;
	}
	if (!(*lst))
		*lst = new;
}
