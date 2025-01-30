/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 17:23:45 by nikitadorof      ###   ########.fr       */
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

void	print_cmd(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
	printf("\n");
}

int	executor(t_shell *shell)
{
	t_cmd	*cmds;
	int		i;

	cmds = cmds_shell_exec(cmds, shell);
	if (!cmds)
		return (-1);
	if (check_pipe(&cmds) == -1)
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
		i = built_ins(cmds, 0);
	else
		exec_duo(cmds, shell);
	free_cmds(&cmds);
	return (i);
}
