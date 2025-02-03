/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:34:47 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/01 18:03:03 by nikitadorof      ###   ########.fr       */
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

	if (!token || !token->content)
		return;
	i = count_quotes(token);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return;
	i = 0;
	j = 0;
	delete_quotes(token, str, i, j);
	if (!str[0] && token->content[0])
	{
		free(str);
		return;
	}
	free(token->content);
	token->content = str;
}

void	remove_quotes(t_token *stack)
{
	t_token *tmp;
	t_token *next_token;

	if (!stack)
		return;
	tmp = stack;
	while (tmp)
	{
		next_token = tmp->next;

		if (string_type(tmp))
		{
			quotes_correct(tmp);
			
			if (next_token && string_type(next_token))
			{
				union_string(tmp);
				quotes_correct(tmp);
				continue;
			}
		}
		tmp = tmp->next;
	}
}
