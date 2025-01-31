/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:33:13 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 13:48:44 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_fork_error(t_cmd *cmd, t_shell *shell)
{
	perror("fork error");
	cleanup_pipes_and_exit(cmd, shell, 1);
}

void	execute_pipeline(t_cmd *cmd, t_shell *shell,
		t_cmd *aux, t_cmd *aux_2)
{
	int	pid;
	int	id;

	pid = 1;
	id = 0;
	while (aux && pid != 0)
	{
		if (aux->id == 0 || aux_2->pipe == 1)
		{
			pid = fork();
			if (pid == -1)
				handle_fork_error(cmd, shell);
			if (pid == 0)
			{
				setup_child_signals();
				exec_child(cmd, aux->id, shell);
			}
		}
		aux_2 = aux;
		id = aux->id;
		aux = aux->next;
	}
	if (pid != 0)
		exec_parent(cmd, id, pid);
}

void	exec_duo(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*aux;
	t_cmd	*aux_2;

	if (!cmd || !shell)
		return ;
	if (check_pipe(&cmd) == -1)
		return ;
	aux = cmd;
	aux_2 = aux;
	execute_pipeline(cmd, shell, aux, aux_2);
}
