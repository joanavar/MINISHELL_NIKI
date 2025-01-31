/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:39:38 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 13:51:00 by camurill         ###   ########.fr       */
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

int	safe_close(int fd)
{
	if (fd > 2)
	{
		if (close(fd) == -1)
		{
			perror("close error");
			return (-1);
		}
	}
	return (0);
}

t_cmd	*close_pipes(t_cmd *cmd, int id)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->id != id)
		{
			if (aux->std_in != 0 && aux->std_in != -1)
				safe_close(aux->std_in);
			if (aux->std_out != 1 && aux->std_out != -1)
				safe_close(aux->std_out);
			if (aux->fd_in != 0 && aux->fd_in != -1)
				safe_close(aux->fd_in);
			if (aux->fd_out != 0 && aux->fd_out != -1)
				safe_close(aux->fd_out);
		}
		aux = aux->next;
	}
	aux = cmd;
	while (aux && aux->id != id)
		aux = aux->next;
	if (!aux)
		return (NULL);
	ft_dups(aux);
	return (aux);
}

void	exec_parent(t_cmd *cmd, int id, int pid)
{
	t_cmd	*aux;
	void	(*old_sigint)(int);
	void	(*old_sigquit)(int);

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
	old_sigint = signal(SIGINT, SIG_IGN);
	old_sigquit = signal(SIGQUIT, SIG_IGN);
	waiting(cmd->shell);
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
}

void	cleanup_pipes_and_exit(t_cmd *cmd, t_shell *shell, int status)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->path)
			free(aux->path);
		if (aux->std_in != 0)
			safe_close(aux->std_in);
		if (aux->std_out != 1)
			safe_close(aux->std_out);
		if (aux->fd_in != 0)
			safe_close(aux->fd_in);
		if (aux->fd_out != 0)
			safe_close(aux->fd_out);
		aux = aux->next;
	}
	clean_data(shell);
	exit(status);
}
