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

static int		count_quotes(t_token *token)
{
	int i;
	char tmp;
	int count;
	
	count = 0;
	i = 0;
	
	while (token->content[i])
	{
		while (token->content[i])
		{
			if (token->content[i] == '\"' || token->content[i] == '\'')
			{
				tmp = token->content[i];
				i++;
				break ;
			}
			i++;
			count++;
		}
		while (token->content[i])
		{
			if (token->content[i] == tmp)
			{
				i++;
				break ;
			}
			i++;
			count++;
		}
	}
	printf("la nueva string tendra de memoria :%d\n", count);
	return (count);
}

static void quotes_correct(t_token *token)
{
	char *str;
	int i;
	char tmp;
	int j;

	i = count_quotes(token);
	str = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (token->content[i])
	{
		while (token->content[i] && !(token->content[i] == '\"' || 
				token->content[i] == '\''))
				str[j++] = token->content[i++];
		if (!token->content[i])
			break;
		if (i == 0 || (token->content[i - 1] == '\"' || 
				token->content[i - 1] == '\''))
			tmp = token->content[i];
		else 
			tmp = token->content[i - 1];
		i++;
		//printf("valor j :%d\n", j);
		while(token->content[i] && token->content[i] != tmp)
		{
			str[j++] = token->content[i++];
			//printf("VALOR DE J :%d\n", j);
		}
		tmp = 0;
		i++;
		if (!token->content[i])
			break;
	}
	str[j] = '\0';
	//printf ("mi content nuevo es :%s\n", str);
	free(token->content);
	token->content = str;
}

void	remove_quotes(t_token *stack)
{
	t_token *tmp;
	char	*tmp_content;

	while(stack)
	{
		if (!stack->next)
			break ;
		if (string_type(stack) && string_type(stack->next))
		{
			tmp = stack->next; // guardo referencia 2do nodo
			tmp_content = stack->content; // guardo referencia 1ra string
			stack->content = ft_strjoin(stack->content, stack->next->content); // fusiono 1era y 2da string, pierdoo referencia 1ra
			stack->next = tmp->next; //asigno siguiente nodo al 3r
			free(tmp_content); // libero 1ra string simple
			free(tmp->content); // libero 2da string simple
			free(tmp); // libero segundo nodo
			quotes_correct(stack);
		}
		else
			stack = stack->next;
	}
	if (stack->type == 0)
		stack = stack->prev;
}
