/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/02/06 16:24:12 by camurill         ###   ########.fr       */
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

static void	aux_b(t_cmd *cmd)
{
	t_cmd	*aux;

	if (!cmd || !cmd->arr_cmd || cmd->arr_cmd[0][0] == '\0')
		return ;
	aux = cmd;
	while (aux)
	{
		aux->builtins = is_builtins(aux->arr_cmd[0]);
		aux = aux->next;
	}
	if (cmd->builtins == 1 && !cmd->next)
	{
		cmd->path = ft_strdup(cmd->arr_cmd[0]);
		if (!cmd->path)
			return ;
	}
}

int	executor(t_shell *shell, t_trust *trust)
{
	int	i;

	i = 0;
	shell->cmds = cmds_shell_exec(shell->cmds, shell);
	if (!shell->cmds || check_pipe(&shell->cmds) == -1)
	{
		if (shell->cmds)
			free_cmds(&shell->cmds);
		return (-1);
	}
	aux_b(shell->cmds);
	shell->cmds = initial_cmd(shell->cmds);
	i = res_exec(shell, trust, i);
	return (i);
}
