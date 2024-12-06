/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:34:47 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/03 20:00:35 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//#include "paquito.h"

int	string_type(t_token *token)
{
	if (token->type == 1)
		return (1);
	else if (token->type == 2)
		return (1);
	else if (token->type == 3)
		return (1);
	else 
		return (0);
}

/*void	remove_quotes(t_token *stack)
{
	t_token *tmp;
	char	*tmp_content;

	while(stack)
	{
		if (string_type(stack) && string_type(stack->next))
		{
			tmp = stack->next; // guardo referencia 2do nodo
			tmp_content = stack->content; // guardo referencia 1ra string
			stack->content = ft_strjoin(stack->content, stack->next->content); // fusiono 1era y 2da string, pierdoo referencia 1ra
			stack->next = tmp->next; //asigno siguiente nodo al 3r
			free(tmp_content); // libero 1ra string simple
			free(tmp->content); // libero 2da string simple
			free(tmp); // libero segundo nodo
		}
		else
			stack = stack->next;
	}
}*/
