/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:42:39 by camurill          #+#    #+#             */
/*   Updated: 2024/12/14 20:43:54 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_type(t_token	*token)
{
	while(token)
	{
		if (token->type == 1 || token->type == 2 || token->type == 3)
			return (0);
		token = token->next;
	}
	return (1);
}
void	get_echo(t_shell *shell)
{
	t_token	*aux;

	aux = shell->eco_token;
	if (check_type(aux->next) == 1)
	{
		printf("\n");
		return ;
	}
	if (!check_type(aux) && !strncmp("-n", aux->next->next->content, 3))
	{
		if (!aux->next->next->next->next)
			return ;
		aux = aux->next->next->next->next;
		while (aux)
		{
			printf("%s", aux->content);
			aux = aux->next;
		}
	}
	else if (!check_type(aux) && strncmp("-n", aux->next->next->content, 3))
		{
			if (!aux->next->next)
				return ;
			aux = aux->next->next;
			while (aux)
			{
				if (aux->type == 0)
				{
					printf(" ");
					aux = aux->next;
				}
				if (aux->next)
					printf("%s", aux->content);
				else if (!aux->next)
					printf("%s\n", aux->content);
				aux = aux->next;
			}
		}
}
