/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/15 15:49:00 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_cmd(char **array)
{
	int i = 0;
	while(array && array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
	printf("\n");
}

int	executor(t_shell *shell)
{
	t_cmd *cmds;
	t_token *tmp;
	cmds = NULL;
	//(void)shell;
	tmp = shell->eco_token;
	print_line(tmp);
	cmds = token_to_cmd(tmp);
	cmds->shell = shell;
	if (!cmds)
		return (-1);
	if (cmds && built_ins(cmds) == -1)
		return (-1);
	if (!cmds->next)
		return (exec_ve(cmds));
	else
		return (exec_duo(cmds));
	//print_cmd(cmds->arr_cmd);make
		//return (0);
	return (0);
}

int	exec_ve(t_cmd *cmd)
{
	int	status;

	if (fork() == 0)
	{
		if (execvp(cmd->arr_cmd[0], cmd->arr_cmd) == -1)
		{
			perror("cmd: ");
			return (EXIT_FAILURE);
		}
	}
	wait(&status);
	return (EXIT_SUCCESS);
}
