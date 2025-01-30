/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lectur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:54:07 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/30 17:42:53 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>



static int	is_caracter_token(char c, t_token **stack)
{
	char	*token;

	token = malloc(sizeof(char) * 2);
	if (!token)
		return (0);
	token[0] = c;
	token[1] = '\0';
	if (!get_token(token, stack))
	{
		free(token);
		return (0);
	}
	return (1);
}

static int	is_redireccion(char *str, int i, t_token **stack)
{
	char	*token;

	token = malloc(sizeof(char) * 3);
	if (!token)
		return (0);
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
		return (0);
	}
	return (1);
}

static int	lectur_line(char *str, t_token **stack, int i)
{
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (!is_caracter_token(str[i], stack))
				return (0);
		}
		else if (str[i] == '|')
		{
			if (!is_caracter_token(str[i], stack))
				return (0);
		}
		else if (str[i] == '>' || str[i] == '<')
		{
			if ((str[i] == '<' && str[i + 1] == '<')
				|| str[i] == '>' && str[i + 1] == '>')
			{
				if (!is_redireccion(str, i, stack))
					return (0);
				i++;
			}
			else if (!is_caracter_token(str[i], stack))
				return (0);
		}
		else
		{
			i = is_string(str, i, stack);
			if (i == -1)
				return (0);
			i--;
		}
		i++;
	}
	return (1);
}

t_token	*lectur_imput(char *str, t_env *env)
{
	int		i;
	t_token	*stack;

	if (!str || !env)
		return (NULL);
	i = 0;
	stack = NULL;
	if (!*str)
		return (NULL);
	if (!lectur_line(str, &stack, i))
	{
		free_token(&stack);
		return (NULL);
	}
	if (syntax_error(&stack))
	{
		free_token(&stack);
		return (NULL);
	}
	expandir(&stack, env);
	remove_quotes(stack);
	return (stack);
}
