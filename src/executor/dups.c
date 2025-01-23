/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:42:27 by camurill          #+#    #+#             */
/*   Updated: 2025/01/21 20:58:11 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void closes_dups(t_cmd *cmd)
{
	if (cmd->std_out != 1)
	{
		cmd->stdout_dup = dup(1);
		dup2(cmd->std_out, 1);
		close(cmd->std_out);
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
	}
	else if (cmd->fd_in != 0)
	{
		cmd->stdout_dup = dup(1);
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
}

void	ft_dups(t_cmd *cmd)
{
	if (cmd->std_in != 0)
	{
		cmd->std_dup = dup(0);
		dup2(cmd->std_in, 0);
		close(cmd->std_in);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
	}
	else if (cmd->fd_in != 0)
	{
		cmd->std_dup = dup(0);
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	closes_dups(cmd);
}
