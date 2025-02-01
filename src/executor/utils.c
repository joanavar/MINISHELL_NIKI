/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:40 by camurill          #+#    #+#             */
/*   Updated: 2025/02/01 18:53:19 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*cmds_shell_exec(t_cmd *cmds, t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->eco_token;
	cmds = token_to_cmd(tmp, shell);
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
				{
					expand_exit_status(tmp, i, shell);
					continue;
				}
				else if (tmp->content[i] == '$')
				{
					expander(tmp, i, env, shell);
					if (!tmp->content[i++])
						i++;
					continue;
				}
				i++;
				if (!tmp->content)
					break ;
			}
		}
		tmp = tmp->next;
	}
}
