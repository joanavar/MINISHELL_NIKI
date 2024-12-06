/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:19:15 by camurill          #+#    #+#             */
/*   Updated: 2024/01/26 02:27:30 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//devolver el 'ultimo valor de la lista
t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
