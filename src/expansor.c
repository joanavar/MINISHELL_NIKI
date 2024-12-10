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

void exchange_expanser(t_token *token, t_env *env, int start, int end, int measure)
{
	char *str;
	int i;
	int j;

	i = -1;
	j = -1;
	len = total;
	str = malloc(sizeof(char *) * len);
	while (++i < start)
		 str[i] = token->content[i];
	while (env->content[++j])
		str[i++] = env->content[j];
	while(token->content[end])
		str[i++] = env->content[end++];
	str[i] = '\0';
	free(token->content);
	token->content = str;

//Tengo que hacerle malloc, nse si se libera bien asi tengo que comprobar proximo dia !!!!!;
//Tengo mi contenido modificado despues de expandir ahora tendria que sustituir el contenido de mi token por mi nueva str;
//getenv;
//measure es la medida de lo que vamos a cambiar

}
void expander(t_token *token, int i, t_env **env)
{
	char * str;
	int j;
	int len;
	t_env *tmp;

	i++;
	j = i;
	if (correct_expansor(token, i))
	{
		while (close_expansor(token, i))
			i++;
		len = i - j;
		str = ft_substr(token->content, j, len);
		tmp = *env;
		while (tmp)
		{
			if (ft_strcmp(str, tmp->value))
				exchange_expanser(token, tmp, j - 1, i, len + 1);
			tmp = tmp->next;
		}

	}
}

void	expandir(t_token **stack)
{
	t_token *tmp;
	int i;
	
	i = 0;
	tmp = *stack;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 3)
		{
			while (token->content[i])
			{
				if (token->content[i] == '$')
					expander(token, i);
				i++;
			}
		}	
		tmp = tmp->next;
	}
}
