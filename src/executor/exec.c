/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/20 14:10:21 by camurill         ###   ########.fr       */
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
	//print_line(tmp);
	cmds = token_to_cmd(tmp);
	cmds->shell = shell;
	if (!cmds)
		return (-1);
	cmds->path = get_path(cmds);
	if (cmds && built_ins(cmds) < 0)
		return (-1);
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
