/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reddit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:17:53 by camurill          #+#    #+#             */
/*   Updated: 2025/02/05 13:29:38 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	redir_l_one(t_cmd *cmd, t_redir *redir)
{
	int		fd;
	t_cmd	*aux;

	aux = cmd;
	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		error_message("File descriptor: Error: fd", NO_CLOSE);
		return ;
	}
	if (aux->std_in != 0)
		close(aux->std_in);
	aux->std_in = fd;
}

static void	redir_r_one(t_cmd *cmd, t_redir *redir)
{
	int		fd;
	t_cmd	*aux;

	aux = cmd;
	fd = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_message("Errors with opens", NO_CLOSE);
		return ;
	}
	if (aux->std_out != 1)
		close(aux->std_out);
	aux->std_out = fd;
}

static void	redir_r_two(t_cmd *cmd, t_redir *redir)
{
	int		fd;
	t_cmd	*aux;

	aux = cmd;
	fd = open(redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		error_message("Errors with opens", NO_CLOSE);
		return ;
	}
	if (aux->std_out != 1)
		close(aux->std_out);
	aux->std_out = fd;
}

static void	res_check(t_cmd *aux)
{
	if (aux->redirs->type == 8)
		redir_l_one(aux, aux->redirs);
	if (aux->redirs->type == 6)
		redir_r_one(aux, aux->redirs);
	if (aux->redirs->type == 7)
		redir_r_two(aux, aux->redirs);
}

int	check_reddir(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*aux;
	int		result;

	if (!cmd->redirs)
		return (-1);
	aux = cmd;
	while (aux->redirs)
	{
		res_check(aux);
		if (aux->redirs->type == 5)
		{
			result = heredoc(aux, shell, aux->redirs->file_name);
			if (result < 0)
			{
				if (shell->exit_status == 130)
				{
					g_signal_received = 130;
					return (0);
				}
				return (result);
			}
		}
		aux->redirs = aux->redirs->next;
	}
	return (0);
}
