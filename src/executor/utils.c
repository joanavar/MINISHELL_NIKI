/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:40 by camurill          #+#    #+#             */
/*   Updated: 2025/01/27 13:41:50 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
void	change_status(t_shell *shell)
{
	
}*/

int	check_pipe(t_cmd **cmd)
{
	t_cmd	*aux;
	int		fd[2];

	if (!cmd)
		return (-1);
	aux = *cmd;
	while (aux->next)
	{
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
			//change_status(shell);
		}
		if (WIFEXITED(exit_status))
		{
			status = WEXITSTATUS(exit_status);
			shell->exit_status = status;
			//change_status(shell);		
		}
	}
	check_signal(g_signal_received);
}