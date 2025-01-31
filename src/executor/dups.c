/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:42:27 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 11:29:21 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_dup_error(int fd, const char *msg)
{
	if (fd == -1)
	{
		perror(msg);
		return (-1);
	}
	return (0);
}

static int	handle_stdin_dup(t_cmd *cmd)
{
	cmd->std_dup = dup(0);
	if (handle_dup_error(cmd->std_dup, "dup error") == -1)
		return (-1);
	if (handle_dup_error(dup2(cmd->std_in, STDIN_FILENO), "dup2 error") == -1)
	{
		close(cmd->std_dup);
		return (-1);
	}
	close(cmd->std_in);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	return (0);
}

static int	handle_fd_in_dup(t_cmd *cmd)
{
	cmd->std_dup = dup(0);
	if (handle_dup_error(cmd->std_dup, "dup error") == -1)
		return (-1);
	if (handle_dup_error(dup2(cmd->fd_in, STDIN_FILENO), "dup2 error") == -1)
	{
		close(cmd->std_dup);
		return (-1);
	}
	close(cmd->fd_in);
	return (0);
}

static int	handle_stdout_dup(t_cmd *cmd)
{
	cmd->stdout_dup = dup(1);
	if (handle_dup_error(cmd->stdout_dup, "dup error") == -1)
		return (-1);
	if (handle_dup_error(dup2(cmd->std_out, STDOUT_FILENO), "dup2 error") == -1)
	{
		close(cmd->stdout_dup);
		return (-1);
	}
	close(cmd->std_out);
	if (cmd->fd_out != 0)
		close(cmd->fd_out);
	return (0);
}

static int	handle_fd_out_dup(t_cmd *cmd)
{
	cmd->stdout_dup = dup(1);
	if (handle_dup_error(cmd->stdout_dup, "dup error") == -1)
		return (-1);
	if (handle_dup_error(dup2(cmd->fd_out, STDOUT_FILENO), "dup2 error") == -1)
	{
		close(cmd->stdout_dup);
		return (-1);
	}
	close(cmd->fd_out);
	return (0);
}

void	ft_dups(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->std_in != 0)
	{
		if (handle_stdin_dup(cmd) == -1)
			return ;
	}
	else if (cmd->fd_in != 0)
	{
		if (handle_fd_in_dup(cmd) == -1)
			return ;
	}
	if (cmd->std_out != 1)
	{
		if (handle_stdout_dup(cmd) == -1)
			return ;
	}
	else if (cmd->fd_out != 0)
	{
		if (handle_fd_out_dup(cmd) == -1)
			return ;
	}
}
