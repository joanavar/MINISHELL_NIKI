/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:34:47 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/05 16:32:32 by joanavar         ###   ########.fr       */
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
	tmp = '\0';
	count = count_quotes_utils(token, i, count, tmp);
	return (count);
}

static void	quotes_correct(t_token *token)
{
	char	*str;
	int		i;
	int		j;

	i = count_quotes(token);
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return ;
	i = 0;
	j = 0;
	delete_quotes(token, str, i, j);
	free(token->content);
	token->content = str;
}

static int	res_remove_quotes(t_token **current)
{
	if (string_type(*current) && string_type((*current)->next))
	{
		quotes_correct((*current)->next);
		union_string(*current);
	}
	else if (!string_type(*current) && string_type((*current)->next))
	{
		quotes_correct((*current)->next);
		(*current) = (*current)->next;
	}
	else
	{
		if (!(*current)->next)
			return (0);
		(*current) = (*current)->next;
	}
	return (1);
}

void	remove_quotes(t_token *stack)
{
	t_token	*current;
	int		i;

	i = 0;
	if (!stack)
		return ;
	current = space_zero(stack);
	while (current)
	{
		if (i == 0)
			quotes_correct(current);
		if (!string_type(current) && string_type(current->next)
			&& !current->next->next)
		{
			quotes_correct(current->next);
			break ;
		}
		else
		{
			if (!res_remove_quotes(&current))
				break ;
		}
		i++;
	}
}
