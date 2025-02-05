/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:48:04 by camurill          #+#    #+#             */
/*   Updated: 2025/02/02 19:11:21 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	syntax_prompt(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			count++;
		i++;
	}
	if ((count % 2) == 0)
		return (1);
	else
		return (0);
}

int	start_shell(t_shell *shell, t_trust *trust)
{
	if (shell->prompt[0] == '\0')
		return (0);
	if (!syntax_prompt(shell->prompt))
	{
		printf("Minishell: syntax error: unexpected end of file\n");
		return (0);
	}
	shell->eco_token = lectur_imput(shell->prompt, shell->env, shell);
	if (!shell->eco_token)
		return (2);
	shell->cmds = token_to_cmd(shell->eco_token, shell);
	if (!shell->cmds)
	{
		free_token(&(shell->eco_token));
		return (2);
	}
	executor(shell, trust);
	if (shell->eco_token)
		free_token(&(shell->eco_token));
	if (shell->cmds)
		free_cmds(&(shell->cmds));
	return (0);
}
