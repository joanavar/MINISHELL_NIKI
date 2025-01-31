/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:34:47 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/31 18:38:34 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	count_quotes(t_token *token)
{
	int		i;
	char	tmp;
	int		count;

	count = 0;
	i = 0;
	count = count_quotes_utils(token, i, count, tmp);
	return (count);
}

static void	quotes_correct(t_token *token)
{
	char	*str;
	int		i;
	char	tmp;
	int		j;

	i = count_quotes(token);
	str = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	delete_quotes(token, str, i, j);
	free(token->content);
	token->content = str;
}

void	remove_quotes(t_token *stack)
{
	t_token	*tmp;
	int		i;

	stack = space_zero(stack);
	i = 0;
	while (stack)
	{
		if (!stack->next)
			break ;
		if (i == 0 && (stack->type == 2 || stack->type == 3))
			quotes_correct(stack);
		if (string_type(stack) && string_type(stack->next))
		{
			quotes_correct(stack->next);
			union_string(stack);
		}
		else if (string_type(stack))
		{
			quotes_correct(stack);
			stack = stack->next;
		}
		else
			stack = stack->next;
		i++;
	}
}
