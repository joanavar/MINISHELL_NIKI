/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 13:21:38 by joanavar         ###   ########.fr       */
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

int	executor(t_shell *shell, t_trust *trust)
{
	t_cmd	*cmds;
	t_token	*tmp;
	int		i;
	int		j;

	cmds = NULL;
	i = 0;
	j = 0;
	cmds = cmds_shell_exec(cmds, shell);
	if (check_pipe(&cmds) == -1)
		return (-1);
	cmds->path = get_path(cmds, shell->env);
	if (!cmds->path)
		return (-1);
	cmds = initial_cmd(cmds);
	if (cmds->path && cmds->builtins == 1 && cmds->next == NULL)
	{
		i = built_ins(cmds, 0, trust);
	}
	else
		exec_duo(cmds, shell, trust);
	return (i);
}
