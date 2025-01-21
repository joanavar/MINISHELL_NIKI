/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:33:13 by camurill          #+#    #+#             */
/*   Updated: 2025/01/21 20:56:25 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->next)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
static t_cmd	*close_pipes(t_cmd *cmd, int id)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->id != id)
		{
			if (aux->std_in != 0)
				close(aux->std_in);
			if (aux->std_out != 1)
				close(aux->std_out);
			if (aux->fd_in != 0)
				close (aux->fd_in);
			if (aux->fd_out != 0)
				close (aux->fd_out);
		}
		aux = aux->next;
	}
	aux = cmd;
	while (aux->id != id)
		aux = aux->next;
	ft_dups(aux);
	return (aux);
}

static void exec_parent(t_cmd *cmd, int id)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->id != id)
		{
			if (aux->std_in != 0)
				close(aux->std_in);
			if (aux->std_out != 1)
				close(aux->std_out);
			if (aux->fd_in != 0)
				close (aux->fd_in);
			if (aux->fd_out != 0)
				close (aux->fd_out);
		}
		aux = aux->next;
	}
	//waiting();
}


void exec_child(t_cmd *cmd, int id)
{
	t_cmd	*aux;

	aux = close_pipes(cmd, id);
	aux->path = get_path(aux);
	if (!aux->path)
	{
		if (aux->shell->exit_status == 0)
			exit (0);
		ft_putstr_fd("Minishell: Command not found: ", 2);
		ft_putendl_fd(aux->arr_cmd[0], 2);
		exit(127);
	}
	if (cmd->builtins != 1)
		mini_exec(cmd);
	else
		built_ins(cmd);
}

void	exec_duo(t_cmd *cmd)
{
	t_cmd	*aux;
	t_cmd	*aux_2;
	int		pid;

	pid = 1;
	aux = cmd;
	aux_2 = aux;
	while (aux && pid != 0)
	{
		if (aux->id == 0 || count_cmd(aux_2) > 0)
			pid = fork();
		if (pid == 0)
			exec_child(cmd, aux->id);
		else if (aux)
		{
			aux_2 = aux;
			aux = aux->next;
		}
	}
	if (pid != 0)
		exec_parent(cmd, aux->id);
}
