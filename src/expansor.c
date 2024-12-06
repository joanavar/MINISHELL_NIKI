/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joanavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:17:46 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/03 20:00:01 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//#include "paquito.h"

int close_expansor(t_token *token, int i)
{
	if (token->content[i] >= 'a' && 
			token->content[i] <= 'z')
		return (1);
	else if (token->content[i] >= 'A' && 
			token->content[i] <= 'Z')
		return (1);
	else if (token->content[i] == '_')
		return (1);
	else if (token->content[i] >= '0' && 
			token->content[i] <= '9')
		return (1);
	return (0);

}
int correct_expansor(t_token *token, int i)
{
	if (token->content[i] >= 'a' && 
			token->content[i] <= 'z')
		return (1);
	else if (token->content[i] >= 'A' && 
			token->content[i] <= 'Z')
		return (1);
	else if (token->content[i] == '_')
		return (1);
	return (0);

}
void $(t_token *token, int i)
{
	char * str;
	int j;
	int len;

	i++;
	j = i;
	if (correct_expansor(token, i))
	{
		while (correct_expansor(token, i))
			i++;
		len = i - j;
		str = ft_substr(token->content, j, len);

	}
}
static void	expansor(t_token *token)
{
	int i;

	i = 0;
	while(token->content[i])
	{
		if (token->content[i] == '$')
			$(token, i);
		i++;
	}
}

void	expandir(t_token **stack)
{
	t_token *tmp;
	
	tmp = *stack;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 3)
			expansor(tmp);
		tmp = tmp->next;
	}
}
