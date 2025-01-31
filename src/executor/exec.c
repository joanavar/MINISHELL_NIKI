/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 18:02:10 by nikitadorof      ###   ########.fr       */
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

static int	handle_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == 8)
		{
			cmd->std_in = heredoc(redir->file_name, shell);
			if (cmd->std_in == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int	executor(t_shell *shell, t_trust *trust)
{
	t_cmd	*cmds;
	int		i;
	int		status;

	cmds = NULL;
	i = 0;
	cmds = cmds_shell_exec(cmds, shell);
	if (!cmds || check_pipe(&cmds) == -1)
	{
		free_cmds(&cmds);
		return (-1);
	}
	if (handle_redirections(cmds, shell) == -1)
	{
		free_cmds(&cmds);
		return (-1);
	}
	cmds->path = get_path(cmds, shell->env);
	if (!cmds->path)
	{
		free_cmds(&cmds);
		return (-1);
	}
	cmds = initial_cmd(cmds);
	if (cmds->path && cmds->builtins == 1 && cmds->next == NULL)
		i = built_ins(cmds, 0, trust);
	else
	{
		exec_duo(cmds, shell, trust);
		i = shell->exit_status;
	}
	if (!cmds->builtins || cmds->next)
		free_cmds(&cmds);
	return (i);
}
