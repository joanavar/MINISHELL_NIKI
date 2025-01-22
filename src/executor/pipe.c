/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joannavarrogomez <joannavarrogomez@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:33:13 by camurill          #+#    #+#             */
/*   Updated: 2025/01/22 17:19:24 by joannavarro      ###   ########.fr       */
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

int	open_file(char *file, int type)
{
	int	fd;

	if (type == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (type == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	return (fd);
}




int	exec_mult(t_cmd *cmd, int size)
{
	pid_t	pid[size];
	int		status;
	int		i;
	int		fd[size];

	i = 1;
	if (pipe(fd) < -1)
		return (-1);
	while (i < size)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			error_message("Fork", NO_CLOSE);
		//if (pid[i] == 0)
		//	child_proccess(fd, cmd->arr_cmd, cmd->shell->env);
		i++;
	}
	//if (pid[i] == 0)
	//	parent_process(fd, ag, env);
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
