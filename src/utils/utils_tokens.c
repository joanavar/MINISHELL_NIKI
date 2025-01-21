/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joanavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:11:34 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/08 17:11:37 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_quotes_utils(t_token *token, int i, int count, char tmp)
{
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
	return (count);
}

int	opcion_syntax(t_token *tmp)
{
	if (tmp->type == 4)
	{
		printf("error syntax\n");
		return (0);
	}
	while (tmp)
	{
		if ((tmp->type == 4 || redir_type(tmp)))
		{
			if (syntax_pipe_or_redi(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	print_token_after_expansor(t_token *stack)
{
	printf("content after expansor:%s\n", stack->content);
}

void	print_line(t_token *tmp)
{
	while (tmp != NULL)
	{
		if (string_type(tmp))
			printf("%s" ,tmp->content);
		else if (tmp->type == 0)
			printf(" ");
		else if (tmp->type == 4)
			printf("|");
		else if (tmp->type == 6)
			printf(">");
		else if (tmp->type == 8)
			printf("<");
		else if (tmp->type == 7)
			printf(">>");
		else if (tmp->type == 5)
			printf("<<");
		tmp = tmp->next;

	}
	printf("\n");
	
}

int	is_heredoc(t_token *token)
{
	t_token *tmp;
	tmp = token;
	while (tmp && tmp->prev->type == 0)
		tmp = tmp->prev;
	if (tmp && tmp->prev->type == 5)
		return (1);
	else
		return (0);

}
