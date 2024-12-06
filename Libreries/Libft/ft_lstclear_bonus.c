/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:51:56 by camurill          #+#    #+#             */
/*   Updated: 2024/03/08 14:13:28 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;
	t_list	*aux;

	buffer = (*lst);
	if (!(buffer == *lst))
		return ;
	while (buffer)
	{
		aux = buffer->next;
		del(buffer->content);
		free(buffer);
		buffer = aux;
	}
	*lst = 0;
}
