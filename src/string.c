/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:42:41 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/03 20:00:46 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//#include "paquito.h"

static int is_command(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '|')	
		return (1);
	else if (c == '<' || c == '>')
		return (1);
	return (0);
}

static int	is_quotes(char *str, int i, t_token **stack, char quote)
{
	char *token;
	int j;
	int count;

	j = i + 1;
	count = 0;
	while ( str[j] && str[j] != quote)
	{
		j++;
		count++;
	}
	j = 0;
	token = malloc(sizeof(char *) * (count + 3));
	if (!token)
		return (0);
	while (str[i] && j < count + 1)// (i < count + 1)
		token[j++] = str[i++];
	token[j++] = quote;
	token[j] = '\0';
	get_token(token, stack);
	return (++i);
}

static int    is_word(char *str, int i, t_token **stack)
{
    char *token;
    int j;
    int count;

    j = i;
    count = 0;
    while (str[j] && !is_command(str[j]))
    {
        count++;
        j++;
    }
    j = 0;
    token = malloc(sizeof(char *) * (count + 1));
    while (str[i] && !is_command(str[i]))
        token[j++] = str[i++];
    token[j] = '\0';
    get_token(token, stack);
	return (i--);
}

int is_string(char *str, int i, t_token **stack)
{
	int j;

	j = 0;
	if (str[i] == '\"' || str[i] == '\'')
		j = is_quotes(str, i, stack, str[i]);//, str[i]); // str[i] sera comilla simple o doble
	else 
		j = is_word(str, i, stack);
	return (j);
}
