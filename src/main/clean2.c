/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:40:02 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 17:54:20 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*aux;
	t_redir	*buffer;

	if (!redir)
		return ;
	buffer = redir;
	while (buffer)
	{
		aux = buffer->next;
		if (buffer->file_name)
			free(buffer->file_name);
		free(buffer);
		buffer = aux;
	}
}

void	free_shell(t_shell **shell)
{
	int	i;

	if (!shell || !*shell)
		return ;
	if ((*shell)->prompt)
		free((*shell)->prompt);
	if ((*shell)->arg)
	{
		i = 0;
		while ((*shell)->arg[i])
		{
			free((*shell)->arg[i]);
			i++;
		}
		free((*shell)->arg);
	}
	free(*shell);
	*shell = NULL;
}
