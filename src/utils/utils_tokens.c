/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:11:34 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/01 18:10:32 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_quotes_utils(t_token *token, int i, int count, char tmp)
{
	if (!token || !token->content)
		return (0);
	while (token->content[i])
	{
		while (token->content[i])
		{
			if (token->content[i] == '\"' || token->content[i] == '\'')
			{
				tmp = token->content[i];
				i++;
				if (!token->content[i])
					return (count);
				break ;
			}
			i++;
			count++;
		}
		res_token(token, &tmp, &i, &count);
		if (!token->content[i] && tmp != 0)
			return (count);
	}
	return (count);
}

int	opcion_syntax(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->type == 4)
	{
		ft_putendl_fd("error syntax", 2);
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
			printf("%s", tmp->content);
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

t_token	*is_heredoc(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	if (tmp->type != 5 || !tmp->next)
		return (tmp);
	tmp = tmp->next;
	while (tmp && tmp->type == 0)
		tmp = tmp->next;
	if (!tmp)
		return (token);
	if (string_type(tmp))
		tmp = tmp->next;
	return (tmp);
}
