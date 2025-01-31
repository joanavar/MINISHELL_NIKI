/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:42:45 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 13:51:25 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_command_not_found(t_cmd *aux, t_shell *shell)
{
	ft_putstr_fd("Minishell: Command not found: ", 2);
	ft_putendl_fd(aux->arr_cmd[0], 2);
	cleanup_pipes_and_exit(aux, shell, 127);
}

void	execute_command(t_cmd *aux, t_shell *shell)
{
	if (aux->builtins != 1)
		mini_exec(aux, shell);
	else
	{
		built_ins(aux, 1);
		cleanup_pipes_and_exit(aux, shell, aux->shell->exit_status);
	}
}

void	exec_child(t_cmd *cmd, int id, t_shell *shell)
{
	t_cmd	*aux;

	aux = close_pipes(cmd, id);
	if (!aux)
		cleanup_pipes_and_exit(NULL, shell, 1);
	if (aux->arr_cmd && aux->arr_cmd[0])
	{
		aux->path = get_path(aux, shell->env);
		if (!aux->path)
			handle_command_not_found(aux, shell);
	}
	else
		cleanup_pipes_and_exit(NULL, shell, 1);
	execute_command(aux, shell);
}