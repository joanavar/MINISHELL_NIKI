/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:48:04 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 18:51:28 by camurill         ###   ########.fr       */
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
	shell->cmds = token_to_cmd(shell->eco_token);
	if (!shell->cmds)
	{
		free_token(&(shell->eco_token));
		ft_putstr_fd("Error with cmds\n", 2);
		exit(2);
	}
	if (executor(shell, trust) == -1)
	{
		free_token(&(shell->eco_token));
		return (1);
	}
	if (shell->eco_token)
		free_token(&(shell->eco_token));
	if (shell->cmds)
		free_cmds(&(shell->cmds));
	return (0);
}
