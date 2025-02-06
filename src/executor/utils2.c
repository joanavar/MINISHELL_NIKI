/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:43:16 by camurill          #+#    #+#             */
/*   Updated: 2025/02/06 17:25:48 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pipe(t_cmd **cmd)
{
	t_cmd	*aux;
	int		fd[2];

	if (!cmd)
		return (-1);
	aux = *cmd;
	while (aux->next)
	{
		aux->pipe = 1;
		if (pipe(fd) == -1)
			return (-1);
		aux->fd_out = fd[1];
		aux->next->fd_in = fd[0];
		aux = aux->next;
	}
	return (0);
}

void	waiting(t_shell *shell)
{
	int	exit_status;
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (wait(&exit_status) != -1)
	{
		if (WIFSIGNALED(exit_status) != 0)
		{
			ft_putstr_fd("\n", 1);
			status = WTERMSIG(exit_status) + 128;
			shell->exit_status = status;
		}
		if (WIFEXITED(exit_status))
		{
			status = WEXITSTATUS(exit_status);
			shell->exit_status = status;
		}
	}
	check_signal();
}
