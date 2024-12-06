/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:16:05 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/03 20:01:11 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//#include "paquito.h"

t_token	*find_last(t_token *stack)
{
	while (stack->next)
		stack = stack->next;
	return (stack);
}

static void	stack_token(t_token *token, t_token **stack)
{
	t_token *last_token;

	last_token = find_last(*stack);
	last_token->next = token;
	token->prev = last_token;
	token->next = NULL;
}
static void	get_type_token(t_token *token)
{
	if (token->content[0] == ' ')
		token->type = 0;
	else if (token->content[0] == '|')
		token->type = 4;
	else if (token->content[0] == '<' && 
			token->content[1] == '<')
			token->type = 5;
	else if (token->content[0] == '<')
		token->type = 8;
	else if (token->content[0] == '>' && 
			token->content[1] == '>')
			token->type = 7;
	else if (token->content[0] == '>')
			token->type = 6;
	else if (token->content[0] == '\'')
			token->type = 2;
	else if (token->content[0] == '\"')
		token->type = 3;
	else 
		token->type = 1;
}

void	get_token(char *str, t_token **stack)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->content = str;
	get_type_token(token);
	if (!(*stack))
	{
		*stack = token;
		token->next = NULL;
	}
	else
		stack_token(token, stack);
		
	print_token(token);
}

void	print_token(t_token *stack)
{

	printf("content :%s\n", stack->content);
	printf("type :%d\n", stack->type);
}



