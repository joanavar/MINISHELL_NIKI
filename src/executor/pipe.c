/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:33:13 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 19:38:42 by nikitadorof      ###   ########.fr       */
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
			if (aux->std_in != 0 && aux->std_in != -1)
				close(aux->std_in);
			if (aux->std_out != 1 && aux->std_out != -1)
				close(aux->std_out);
			if (aux->fd_in != 0 && aux->fd_in != -1)
				close(aux->fd_in);
			if (aux->fd_out != 0 && aux->fd_out != -1)
				close(aux->fd_out);
		}
		aux = aux->next;
	}
	aux = cmd;
	while (aux->id != id)
		aux = aux->next;
	if (!aux)
		return (NULL);
	ft_dups(aux);
	return (aux);
}

static void	exec_parent(t_cmd *cmd, int id, int pid)
{
	t_cmd	*aux;
	int		status;

	aux = cmd;
	while (aux)
	{
		if (aux->std_in != 0)
			close(aux->std_in);
		if (aux->std_out != 1)
			close(aux->std_out);
		if (aux->fd_out != 0)
			close(aux->fd_out);
		if (aux->fd_in != 0)
			close(aux->fd_in);
		aux = aux->next;
	}
	waiting(cmd->shell);
}

void	exec_child(t_cmd *cmd, int id, t_shell *shell, t_trust *trust)
{
	t_cmd	*aux;
	int		exit_status;

	aux = close_pipes(cmd, id);
	aux->path = get_path(aux, shell->env);
	if (!aux->path)
	{
		if (aux->shell->exit_status == 130)
		{
			clean_data(shell);
			exit(130);
		}
		if (aux->shell->exit_status == 0)
			exit(0);
		ft_putstr_fd("Minishell: Command not found: ", 2);
		ft_putendl_fd(aux->arr_cmd[0], 2);
		clean_data(shell);
		exit(127);
	}
	if (aux->builtins != 1)
		mini_exec(aux, shell);
	else
	{
		exit_status = built_ins(aux, 1, trust);
		built_ins(aux, 1, trust);
		clean_data(shell);
		exit(exit_status);
	}
}

void	exec_duo(t_cmd *cmd, t_shell *shell, t_trust *trust)
{
	t_cmd	*aux;
	t_cmd	*aux_2;
	int		pid;
	int		id;

	pid = 1;
	id = 0;
	aux = cmd;
	aux_2 = aux;
	while (aux && pid != 0)
	{
		if (aux->id == 0 || aux_2->pipe == 1)
			pid = fork();
		if (pid == 0)
			exec_child(cmd, aux->id, shell, trust);
		else if (aux != 0)
		{
			aux_2 = aux;
			id = aux->id;
			aux = aux->next;
		}
	}
	if (pid != 0)
		exec_parent(cmd, id, pid);
	if (cmd->builtins == 1 && !cmd->next)
	{
		if (shell->exit_status == 130)
			return;
		built_ins(cmd, 0, trust);
		return;
	}
}
