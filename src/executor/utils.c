/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:40 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 16:38:11 by nikitadorof      ###   ########.fr       */
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
	check_signal(g_signal_received);
}

t_cmd	*cmds_shell_exec(t_cmd *cmds, t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->eco_token;
	cmds = token_to_cmd(tmp);
	if (!cmds)
		return (NULL);
	cmds->shell = shell;
	if (!cmds->shell)
		return (NULL);
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
				if (!tmp->content[i + 1] && tmp->content[i] == '$')
					return ;
				else if (tmp->content[i] == '$'
					&& tmp->content[i + 1] == '?')
					return ;
				else if (tmp->content[i] == '$')
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
