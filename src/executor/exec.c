/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/14 22:11:43 by camurill         ###   ########.fr       */
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

static char *union_cmd(t_cmd *cmd)
{
	int i;
	char *new_cmd;

	i = 0;
	while(cmd->arr_cmd[i])
	{
		if (i == 0)
			new_cmd = ft_strdup(cmd->arr_cmd[i]);
		else
		{
			new_cmd = ft_strjoin(new_cmd, " ");
			new_cmd = ft_strjoin(new_cmd, cmd->arr_cmd[i]);
		}
		i++;
	}
	return (new_cmd);

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
	cmds->path = union_cmd(cmds);
	printf("%s\n", cmds->path);
	if (!cmds->next)
		return (exec_ve(cmds));
	//print_cmd(cmds->arr_cmd);make
		//return (0);
	return (0);
}

int	exec_ve(t_cmd *cmd)
{
	int	status;

	if (fork() == 0)
		execvp(cmd->arr_cmd[0], cmd->arr_cmd);
	wait(&status);
	return (EXIT_SUCCESS);
}
