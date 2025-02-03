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

int	start_shell(t_shell *shell, t_trust *trust)
{
	if (shell->prompt[0] == '\0')
		return (0);
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
