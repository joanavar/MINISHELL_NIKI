/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:11:34 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/31 16:45:27 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	arr_size(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

t_token	*space_zero(t_token *token)
{
	t_token	*tmp;

	if (!token->next)
		return (NULL);
	tmp = token->next;
	while (tmp->type == 0)
		tmp = tmp->next;
	return (tmp);
}

int	add_first_redir(t_token *token, t_cmd *cmd)
{
	int		filename_size;
	t_token	*tmp;

	tmp = space_zero(token);
	if (!tmp)
		return (0);
	filename_size = ft_strlen(tmp->content);
	cmd->redirs = malloc(sizeof(t_redir) * 1);
	if (!cmd->redirs)
		return (0);
	cmd->redirs->type = token->type;
	cmd->redirs->file_name = ft_strdup(tmp->content);
	if (!cmd->redirs->file_name)
		return (0);
	cmd->redirs->fd = -1;
	cmd->redirs->next = NULL;
	if (cmd->redirs->type == 5)
		heredoc(cmd->redirs->file_name, cmd->shell);
	check_reddir(cmd);
	return (1);
}

int	add_rest_redir(t_token *token, t_cmd *cmd)
{
	t_redir	*tmp_redir;
	t_token	*tmp_token;

	tmp_token = space_zero(token);
	if (!tmp_token)
		return (0);
	tmp_redir = cmd->redirs;
	while (tmp_redir->next)
		tmp_redir = tmp_redir->next;
	tmp_redir->next = malloc(sizeof(t_redir) * 1);
	if (!tmp_redir->next)
		return (0);
	tmp_redir->next->type = token->type;
	tmp_redir->next->file_name = ft_strdup(tmp_token->content);
	if (!tmp_redir->next->file_name)
		return (0);
	tmp_redir->next->fd = -1;
	tmp_redir->next->next = NULL;
	if (tmp_redir->next->type == 5)
		heredoc(tmp_redir->next->file_name, cmd->shell);
	check_reddir(cmd);
	return (1);
}

int	add_redir(t_token *token, t_cmd *cmd)
{
	if (!cmd->redirs)
	{
		if (!add_first_redir(token, cmd))
			return (2);
	}
	else
	{
		if (!add_rest_redir(token, cmd))
			return (2);
	}
	return (1);
}
