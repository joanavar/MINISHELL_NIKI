/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reddit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:17:53 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 21:12:57 by camurill         ###   ########.fr       */
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

static void	redir_r_two(t_cmd *cmd, t_redir *redir)
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

int check_reddir(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*aux;

	if (!cmd->redirs)
		return (-1);
	aux = cmd;
	while (aux->redirs)
	{
		if (aux->redirs->type == 8)
			redir_l_one(aux, aux->redirs);
		if (aux->redirs->type == 6)
			redir_r_one(aux, aux->redirs);
		if (aux->redirs->type == 7)
			redir_r_two(aux, aux->redirs);
		if (aux->redirs->type == 5)
			return (heredoc(aux, shell, aux->redirs->file_name));
		aux->redirs = aux->redirs->next;
	}
	return (0);
}
