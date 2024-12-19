/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:40:02 by camurill          #+#    #+#             */
/*   Updated: 2024/12/13 19:26:31 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_data(t_shell **shell)
{
	if ((*shell)->prompt)
	{
		free((*shell)->prompt);
		(*shell)->prompt = NULL;
	}
	if ((*shell)->env)
		free_env(&((*shell)->env));
	if ((*shell)->eco_token)
		//free_token(&((*shell)->eco_token));
	if ((*shell)->arg)
		free_matrix((*shell)->arg);
	free((*shell));
}
void	free_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	if (!matrix || !(*matrix))
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	free_env(t_env **lst)
{
	t_env	*buffer;
	t_env	*aux;

	buffer = (*lst);
	if (!lst || !*lst)
        return ;
	while (buffer)
	{
		aux = buffer->next;
		if (buffer->content)
			free(buffer->content);
		if (buffer->value)
			free(buffer->value);
		free(buffer);
		buffer = aux;
	}
	*lst = NULL;
}

void free_token(t_token **lst) //Corregir, peta con valores nulos
{
    t_token *buffer;
    t_token *aux;

    if (!lst || !(*lst))
        return ;
    buffer = *lst;
    while (buffer) 
	{
        aux = buffer->next;                
        free(buffer->content);   
        free(buffer);                
        buffer = aux;                
    }
    *lst = NULL;                     
}