/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lectur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:54:07 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/01 19:21:49 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	is_caracter_token(char c, t_token **stack)
{
	char	*token;

	token = malloc(sizeof(char) * 2);
	if (!token)
		return ;
	token[0] = c;
	token[1] = '\0';
	if (!get_token(token, stack))
	{
		free(token);
		return ;
	}
}

static void	is_redireccion(char *str, int i, t_token **stack)
{
	char	*token;

	token = malloc(sizeof(char) * 3);
	if (!token)
		return ;
	if (str[i] == '<' && str[i + 1] == '<')
	{
		token[0] = '<';
		token[1] = '<';
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		token[0] = '>';
		token[1] = '>';
	}
	token[2] = '\0';
	if (!get_token(token, stack))
	{
		free(token);
		return ;
	}
}

static void	lectur_line(char *str, t_token **stack, int i)
{
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == ' ')
			is_caracter_token(str[i], stack);
		else if (str[i] == '|')
			is_caracter_token(str[i], stack);
		else if (str[i] == '>' || str[i] == '<')
		{
			if ((str[i] == '<' && str[i + 1] == '<')
				|| str[i] == '>' && str[i + 1] == '>')
			{
				is_redireccion(str, i, stack);
				i++;
			}
			else
				is_caracter_token(str[i], stack);
		}
		else
			i = is_string(str, i, stack) - 1;
		i++;
	}
}

t_token	*lectur_imput(char *str, t_env *env, t_shell *shell)
{
	int		i;
	t_token	*stack;

	i = 0;
	stack = NULL;
	if (!*str)
		return (NULL);
	lectur_line(str, &stack, i);
	if (syntax_error(&stack))
		return (NULL);
	expandir(&stack, env, shell);
	remove_quotes(stack);
	printf("tester %s\n", stack->next->content);
	return (stack);
}
