/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joannavarrogomez <joannavarrogomez@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/02/03 19:40:43 by joannavarro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_cmd	*initial_cmd(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	aux = cmd;
	i = 0;
	while (cmd)
	{
		cmd->id = i;
		cmd = cmd->next;
		i++;
	}
	return (aux);
}

int	executor(t_shell *shell, t_trust *trust)
{
	int		i;

	i = 0;
	shell->cmds = cmds_shell_exec(shell->cmds, shell);
	if (!shell->cmds || check_pipe(&shell->cmds) == -1)
	{
		if (shell->cmds)
			free_cmds(&shell->cmds);
		return (-1);
	}
	shell->cmds->path = get_path(shell->cmds, shell->env);
	if (!shell->cmds->path)
	{
		free_cmds(&shell->cmds);
		return (-1);
	}
	shell->cmds = initial_cmd(shell->cmds);
	if (shell->cmds->path && shell->cmds->builtins == 1 && shell->cmds->next == NULL)
		i = built_ins(shell->cmds, 0, trust);
	else
	{
		exec_duo(shell->cmds, shell, trust);
		i = shell->exit_status;
	}
	if (shell->cmds)
		free_cmds(&shell->cmds);
	return (i);
}
