/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:42:27 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 17:04:27 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	printf_dups(t_cmd *cmd)
{
	t_cmd	*aux;

	if (!cmd)
		return;
	aux = cmd;
	while (aux)
	{
		printf("cmd->std_in: %i\n", aux->std_in);
		printf("cmd->std_out: %i\n", aux->std_out);
		printf("cmd->std_error: %i\n", aux->std_error);
		printf("cmd->pipe_in: %i\n", aux->fd_in);
		printf("cmd->pipe_out: %i\n", aux->fd_out);
		printf("cmd->pipe_id: %i\n", aux->pipe);
		aux = aux->next;
	}
}

static int	handle_dup_error(int fd, const char *msg)
{
	if (fd == -1)
	{
		perror(msg);
		return (-1);
	}
	return (0);
}

static void	closes_dups(t_cmd *cmd)
{
	if (!cmd)
		return;

	if (cmd->std_out != 1)
	{
		cmd->stdout_dup = dup(1);
		if (handle_dup_error(cmd->stdout_dup, "dup error") == -1)
			return;
		if (handle_dup_error(dup2(cmd->std_out, STDOUT_FILENO), "dup2 error") == -1)
		{
			close(cmd->stdout_dup);
			return;
		}
		close(cmd->std_out);
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
	}
	else if (cmd->fd_out != 0)
	{
		cmd->stdout_dup = dup(1);
		if (handle_dup_error(cmd->stdout_dup, "dup error") == -1)
			return;
		if (handle_dup_error(dup2(cmd->fd_out, STDOUT_FILENO), "dup2 error") == -1)
		{
			close(cmd->stdout_dup);
			return;
		}
		close(cmd->fd_out);
	}
}

void	ft_dups(t_cmd *cmd)
{
	if (!cmd)
		return;

	if (cmd->std_in != 0)
	{
		cmd->std_dup = dup(0);
		if (handle_dup_error(cmd->std_dup, "dup error") == -1)
			return;
		if (handle_dup_error(dup2(cmd->std_in, STDIN_FILENO), "dup2 error") == -1)
		{
			close(cmd->std_dup);
			return;
		}
		close(cmd->std_in);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
	}
	else if (cmd->fd_in != 0)
	{
		cmd->std_dup = dup(0);
		if (handle_dup_error(cmd->std_dup, "dup error") == -1)
			return;
		if (handle_dup_error(dup2(cmd->fd_in, STDIN_FILENO), "dup2 error") == -1)
		{
			close(cmd->std_dup);
			return;
		}
		close(cmd->fd_in);
	}
	closes_dups(cmd);
}
