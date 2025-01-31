/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:40 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 20:52:31 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pipe(t_cmd **cmd)
{
	t_cmd	*aux;
	int		fd[2];
	int		id;

	if (!cmd || !*cmd)
		return (-1);
	aux = *cmd;
	id = 0;
	while (aux->next)
	{
		aux->id = id++;
		aux->pipe = 1;
		if (pipe(fd) == -1)
		{
			perror("pipe error");
			return (-1);
		}
		aux->fd_out = fd[1];
		aux->next->fd_in = fd[0];
		aux = aux->next;
	}
	aux->id = id;
	aux->pipe = 0;  // El último comando no tiene pipe
	return (0);
}

void	waiting(t_shell *shell)
{
	int		exit_status;
	int		status;
	void	(*old_sigint)(int);
	void	(*old_sigquit)(int);

	old_sigint = signal(SIGINT, SIG_IGN);
	old_sigquit = signal(SIGQUIT, SIG_IGN);
	
	while (wait(&exit_status) != -1)
	{
		if (WIFSIGNALED(exit_status) != 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			status = WTERMSIG(exit_status) + 128;
			shell->exit_status = status;
		}
		if (WIFEXITED(exit_status))
			shell->exit_status = WEXITSTATUS(exit_status);
	}
	
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
	check_signal(g_signal_received);
}

t_cmd	*cmds_shell_exec(t_cmd *cmds, t_shell *shell)
{
	t_token	*tmp;

	if (!shell)
		return (NULL);
	tmp = shell->eco_token;
	cmds = token_to_cmd(tmp);
	if (!cmds)
		return (NULL);
	cmds->shell = shell;
	if (!cmds->shell)
	{
		free_cmds(&cmds);
		return (NULL);
	}
	return (cmds);
}

t_token	*expansor_res(t_token *tmp)
{
	if (tmp->type == 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	if (tmp->type == 5)
	{
		tmp = is_heredoc(tmp);
		if (!(tmp->next))
			return (NULL);
	}
	return (tmp);
}

void	travel_expansor(t_token *tmp, t_env *env)
{
	int	i;

	while (tmp)
	{
		i = 0;
		tmp = expansor_res(tmp);
		if (!tmp)
			return ;
		if ((tmp->type == 1 || tmp->type == 3))
		{
			while (tmp->content[i])
			{
				if (tmp->content[i] == '$')
				{
					expander(tmp, i, env);
					continue ;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}
