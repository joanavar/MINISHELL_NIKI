/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joannavarrogomez <joannavarrogomez@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:34:47 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/04 21:02:22 by joanavar         ###   ########.fr       */
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
}

void	remove_quotes(t_token *stack)
{
	t_token	*current;
	int		i;
	t_token	*tmp;

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
			printf("hola\n");
			quotes_correct(current->next);
			break ;
		}
		if (string_type(current) && string_type(current->next))
		{
			printf("antes :%s\n", current->content);
			quotes_correct(current->next);
			union_string(current);
			printf("despueees :%s\n", current->content);
		}
		else if (!string_type(current) && string_type(current->next))
		{
			printf("ENTRO?\n");
			printf("antes :%s\n", current->content);
			quotes_correct(current->next);
			printf("despues :%s\n", current->content);
			current = current->next;
		}
		else
		{
			if (!current->next)
				break ;
			current = current->next;
		}
		i++;
	}
}
