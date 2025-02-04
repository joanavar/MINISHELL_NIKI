/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:40 by camurill          #+#    #+#             */
/*   Updated: 2025/02/04 14:48:46 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*cmds_shell_exec(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*tmp;

	tmp = cmds;
	if (!cmds)
		return (NULL);
	tmp->shell = shell;
	if (!tmp->shell)
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
		tmp = is_heredoc(tmp);
	return (tmp);
}

void	expand_exit_status(t_token *token, int i, t_shell *shell)
{
	char	*before;
	char	*after;
	char	*exit_str;
	char	*result;

	before = ft_substr(token->content, 0, i);
	after = ft_strdup(token->content + i + 2);
	exit_str = ft_itoa(shell->exit_status);
	result = ft_strjoin(before, exit_str);
	free(before);
	free(exit_str);
	before = result;
	result = ft_strjoin(before, after);
	free(before);
	free(after);
	free(token->content);
	token->content = result;
}

void	travel_expansor(t_token *tmp, t_env *env, t_shell *shell)
{
	while (tmp)
	{
		tmp = expansor_res(tmp);
		if (!tmp)
			return ;
		if ((tmp->type == 1 || tmp->type == 3))
		{
			if (!res_travel(tmp, env, shell))
				return ;	
		}
		tmp = tmp->next;
	}
}
