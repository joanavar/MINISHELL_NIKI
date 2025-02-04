/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joannavarrogomez <joannavarrogomez@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:34:47 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/23 19:14:08 by joannavarro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//#include "paquito.h"

int	string_type(t_token *token)
{
	if (!token)
		return (0);
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
	//printf("%s\n", token->content);
}

void	remove_quotes(t_token *stack)
{
	t_token *current;
	int		i;
	t_token *tmp;

	i = 0;
	if (!stack)
		return;
	current = space_zero(stack);
	//printf("%s de\n", current->content);
	while (current)
	{
		if (i == 0)
			quotes_correct(current);
		if (!string_type(current) && string_type(current->next) && !current->next->next)
		{
			quotes_correct(current->next);
			break;
		}
		if (string_type(current) && string_type(current->next))
		{
			quotes_correct(current->next);
			union_string(current);
		}
		else if (string_type(current))
		{
			if (!current->next)
				break ;
			quotes_correct(current);
			current = current->next;
		}
		else
			current = current->next;
		i++;
	}
	//if (!current->next && string_type(current))
	//	quotes_correct(current);
}
