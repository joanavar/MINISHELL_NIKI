/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:34:15 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/03 20:00:59 by joanavar         ###   ########.fr       */
/*   Updated: 2024/11/26 16:12:08 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//#include "paquito.h"

int	redir_type(t_token *token)
{
	if (token->type == 5)
		return (1);
	else if (token->type == 6)
		return (1);
	else if (token->type == 7)
		return (1);
	else if (token->type == 8)
		return (1);
	else 
		return (0);

}

static int	syntax_pipe(t_token *token)
{
	if (token->type == 4 && (token->next->type == 4))
	{
		printf("Error Syntax pipe\n");
		return (1);
	}
	else if (token->type == 4 && (token->next->type == 0))
	{
		token = token->next;
		while(token->type == 0)
			token = token->next;
		if (token->type == 4)
		{
			printf("Error Syntax pipe\n");
			return (1);
		}
	} 
	return (0);
}

static int syntax_redi(t_token *token)
{
	if (redir_type(token) && redir_type(token->next))
	{
		printf ("Error syntax redi\n");
		return (1);
	}
	else if (redir_type(token) && (token->next->type == 0))
	{
		token = token->next;
		while (token->type == 0)
			token = token->next;
		if (redir_type(token))
		{
			printf("Error syntax redi\n");
			return (1);
		}
	}
	return (0);
}
static int syntax_pipe_or_redi(t_token *token)
{
	if (syntax_pipe(token))
		return (1);
	else if (syntax_redi(token))
		return (1);
	else 
		return (0);
}

int	syntax_error(t_token **stack)
{
	t_token *tmp;
	
	tmp = find_last(*stack);
	if (!string_type(tmp))
	{
		printf("ERROR SYNTAX\n");
		return (0);
	}
	else 
		tmp = *stack;
		if (tmp->type == 4)
		{
		printf("error syntax\n");
		return (0);
		}
		while (tmp)
		{
			if ((tmp->type == 4 || redir_type(tmp)))
			{
				if(syntax_pipe_or_redi(tmp))
					return (1);
			}
			tmp = tmp->next;
		}
		return (0);
}
