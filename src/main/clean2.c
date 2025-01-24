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

void    free_redirs(t_redir *redir)
{
    t_redir *aux;
    t_redir *buffer;

    buffer = redir;
    while (buffer)
    {
        aux = buffer->next;
        free(buffer->file_name);
        free(buffer);
        buffer = aux;
    }
    redir = NULL;
}

void    free_shell(t_shell *shell)
{
    int i;

    i = 0;
    free(shell->prompt);
    while (shell->arg[i])
    {
        free(shell->arg[i]);
        i++;
    }
    free(shell->arg);
    shell = NULL;
}