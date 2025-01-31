/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:33:13 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 11:34:38 by nikitadorof      ###   ########.fr       */
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

static int	safe_close(int fd)
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

static t_cmd	*close_pipes(t_cmd *cmd, int id)
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

static void	exec_parent(t_cmd *cmd, int id, int pid)
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

static void	cleanup_pipes_and_exit(t_cmd *cmd, t_shell *shell, int status)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux)
	{
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

static void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	handle_command_not_found(t_cmd *aux, t_shell *shell)
{
	if (aux->shell->exit_status == 0)
		cleanup_pipes_and_exit(aux, shell, 0);
	ft_putstr_fd("Minishell: Command not found: ", 2);
	ft_putendl_fd(aux->arr_cmd[0], 2);
	cleanup_pipes_and_exit(aux, shell, 127);
}

static void	execute_command(t_cmd *aux, t_shell *shell)
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
	aux->path = get_path(aux, shell->env);
	if (!aux->path)
		handle_command_not_found(aux, shell);
	execute_command(aux, shell);
}

static void	handle_fork_error(t_cmd *cmd, t_shell *shell)
{
	perror("fork error");
	cleanup_pipes_and_exit(cmd, shell, 1);
}

static void	execute_pipeline(t_cmd *cmd, t_shell *shell, t_cmd *aux, t_cmd *aux_2)
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

