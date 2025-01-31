/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:34:15 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/31 17:01:53 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		while (token->type == 0)
			token = token->next;
		if (token->type == 4)
		{
			printf("Error Syntax pipe\n");
			return (1);
		}
	}
	return (0);
}

static int	syntax_redi(t_token *token)
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

int	syntax_pipe_or_redi(t_token *token)
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
	t_token	*tmp;

	if (!(*stack))
		return (-1);
	tmp = find_last(*stack);
	if (!(string_type(tmp) || tmp->type == 0))
	{
		printf("ERROR SYNTAX\n");
		return (1);
	}
	else
		tmp = *stack;
	if (opcion_syntax(tmp))
		return (1);
	return (0);
}