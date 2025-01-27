/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:40:02 by camurill          #+#    #+#             */
/*   Updated: 2025/01/24 20:23:11 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_data(t_shell *shell)
{
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (shell->env)
		free_env(shell->env);
	if (shell->eco_token)
		free_token(&(shell->eco_token));
	if (shell->arg)
		free_matrix(shell->arg);
	if (shell->cmds)
		free_cmds(&(shell->cmds));
	//free_shell(shell);
	free(shell);
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

void	free_env(t_env *lst)
{
	t_env	*buffer;
	t_env	*aux;

	buffer = lst;
	if (!lst)
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
}

void free_token(t_token **lst) //Corregir, peta con valores nulos
{
    t_token *buffer;
    t_token *aux;

    if (!lst)
        return ;
    buffer = *lst;
    while (buffer) 
	{
        aux = buffer->next;                
        free(buffer->content);   
        free(buffer);                
        buffer = aux;                
    }
	lst = NULL;                
}

void free_cmds(t_cmd **cmds)
{
    t_cmd   *buffer;
    t_cmd   *aux;
    int     i;

    if (!cmds || !(*cmds))
        return ;
    buffer = *cmds;
    while (buffer)
    {
        aux = buffer->next;
        if (buffer->arr_cmd)
        {
            i = 0;
            while (buffer->arr_cmd[i])
                free(buffer->arr_cmd[i++]);
            free(buffer->arr_cmd);
        }
        if (buffer->path)
            free(buffer->path);
        if (buffer->redirs)
            free_redirs(buffer->redirs);
        free(buffer);
        buffer = aux;
    }
    *cmds = NULL;
}
