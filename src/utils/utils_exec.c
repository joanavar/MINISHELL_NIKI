/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:11:34 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/02 19:11:37 by camurill         ###   ########.fr       */
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
	while (tmp->next && tmp->type == 0)
		tmp = tmp->next;
	return (tmp);
}

int	add_first_redir(t_token *token, t_cmd *cmd, t_shell *shell)
{
	t_token	*tmp;

	tmp = space_zero(token);
	if (!tmp)
		return (0);
	cmd->redirs = malloc(sizeof(t_redir));
	if (!cmd->redirs)
		return (0);
	memset(cmd->redirs, 0, sizeof(t_redir));
	cmd->redirs->type = token->type;
	cmd->redirs->file_name = ft_strdup(tmp->content);
	if (!cmd->redirs->file_name)
	{
		free(cmd->redirs);
		cmd->redirs = NULL;
		return (0);
	}
	cmd->redirs->fd = -1;
	cmd->redirs->next = NULL;
	if (check_reddir(cmd, shell) < 0)
	{
		free(cmd->redirs->file_name);
		free(cmd->redirs);
		cmd->redirs = NULL;
		return (0);
	}
	return (1);
}

int	add_rest_redir(t_token *token, t_cmd *cmd, t_shell *shell)
{
	t_redir	*tmp_redir;
	t_token	*tmp_token;

	tmp_token = space_zero(token);
	if (!tmp_token)
		return (0);
	tmp_redir = cmd->redirs;
	if (!tmp_redir)
		return (add_first_redir(token, cmd, shell));
	while (tmp_redir->next)
		tmp_redir = tmp_redir->next;
	tmp_redir->next = malloc(sizeof(t_redir));
	if (!tmp_redir->next)
		return (0);
	memset(tmp_redir->next, 0, sizeof(t_redir));
	tmp_redir->next->type = token->type;
	tmp_redir->next->file_name = ft_strdup(tmp_token->content);
	if (!tmp_redir->next->file_name)
	{
		free(tmp_redir->next);
		tmp_redir->next = NULL;
		return (0);
	}
	tmp_redir->next->fd = -1;
	tmp_redir->next->next = NULL;
	/*if (check_reddir(cmd, shell) < 0)
	{
		free(tmp_redir->next->file_name);
		free(tmp_redir->next);
		tmp_redir->next = NULL;
		return (0);
	}*/
	return (1);
}

int	add_redir(t_token *token, t_cmd *cmd, t_shell *shell)
{
	int	ret;

	if (!cmd->redirs)
	{
		ret = add_first_redir(token, cmd, shell);
		if (!ret)
			return (2);
	}
	else
	{
		ret = add_rest_redir(token, cmd, shell);
		if (!ret)
			return (2);
	}
	return (1);
}
