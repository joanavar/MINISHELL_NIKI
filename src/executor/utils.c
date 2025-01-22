/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:40 by camurill          #+#    #+#             */
/*   Updated: 2025/01/22 16:44:21 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
void	change_status(t_shell *shell)
{
	
}*/

int	check_pipe(t_token **tokens, t_cmd **last)
{
	int		fd[2];

	if (!(*tokens) || !(*last))
		return (-1);
	(*last)->pipe = 1;
	if (pipe(fd) == -1)
		return (-1);
	(*last)->fd_out = fd[1];
	if (!(*last)->next)
		return (0);
	else
		(*last)->next->fd_in = fd[0];//Aqui falla
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