/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:36:52 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 13:53:20 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_dup_error(int fd, const char *msg)
{
	if (fd == -1)
	{
		perror(msg);
		return (-1);
	}
	return (0);
}

int	handle_stdin_dup(t_cmd *cmd)
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

int	handle_fd_in_dup(t_cmd *cmd)
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