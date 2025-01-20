/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:33:13 by camurill          #+#    #+#             */
/*   Updated: 2025/01/20 12:53:21 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->arr_cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
/*void	change_proccess(int *p_fd, char **ag, char **env)
{
	int	fd;

	fd = open_file(ag[1], 0);
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_error(3, ag[1]);
	if (dup2(p_fd[1], STDOUT_FILENO) < 0)
		ft_error(3, ag[4]);
	close(p_fd[0]);
	funtion_exe(ag[2], env);
}*/


int	exec_mult(t_cmd *cmd, int size)
{
	pid_t	pid[size];
	int		status;
	int		i;
	int		fd[size];

	i = 0;
	if (pipe(fd) < -1)
		return (-1);
	while (i < size)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			error_message("Fork", NO_CLOSE);
		/*if (pid[i] == 0)
			change_proccess(fd, cmd->arr_cmd, cmd->shell->env);*/
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[0], &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}

int	exec_duo(t_cmd *cmd)
{
	int	size;

	size = count_cmd(cmd);
	exec_mult(cmd , size);
	return (EXIT_SUCCESS);
}
