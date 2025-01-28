/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:42:27 by camurill          #+#    #+#             */
/*   Updated: 2025/01/28 15:35:32 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	printf_dups(t_cmd *cmd)
{
	t_cmd	*aux;

	cmd = aux;
	while (aux)
	{
		printf("cmd->std_in: %i\n", aux->std_in);
		printf("cmd->std_out: %i\n", aux->std_out);
		printf("cmd->std_error: %i\n", aux->std_error);
		printf("cmd->pipe_in: %i\n", aux->fd_in);
		printf("cmd->pipe_in: %i\n", aux->fd_out);
		printf("cmd->pipe_id: %i\n", aux->pipe);
		aux = aux->next;
	}
}

static void	closes_dups(t_cmd *cmd)
{
	if (cmd->std_out != 1)
	{
		cmd->stdout_dup = dup(1);
		dup2(cmd->std_out, STDOUT_FILENO);
		close(cmd->std_out);
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
	}
	else if (cmd->fd_out != 0)
	{
		cmd->stdout_dup = dup(1);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	ft_dups(t_cmd *cmd)
{
	if (cmd->std_in != 0)
	{
		cmd->std_dup = dup(0);
		dup2(cmd->std_in, STDIN_FILENO);
		close(cmd->std_in);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
	}
	else if (cmd->fd_in != 0)
	{
		cmd->std_dup = dup(0);
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	closes_dups(cmd);
}
