/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:34:47 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/30 17:37:54 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

	if (!token || !token->content)
		return;
	i = count_quotes(token);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return ;
	i = 0;
	j = 0;
	delete_quotes(token, str, i, j);
	free(token->content);
	token->content = str;
}

void	remove_quotes(t_token *stack)
{
	t_token *current;

	if (!stack)
		return;
	current = stack;
	while (current)
	{
		if (!current->next)
			break;
		if (string_type(current) && string_type(current->next))
		{
			union_string(current);
			if (current->content)
				quotes_correct(current);
		}
		else if (string_type(current))
		{
			quotes_correct(current);
			current = current->next;
		}
		else
			current = current->next;
	}
	if (!current->next && string_type(current))
		quotes_correct(current);
}
