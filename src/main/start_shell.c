/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:48:04 by camurill          #+#    #+#             */
/*   Updated: 2025/01/14 16:36:49 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	start_shell(t_shell *shell)
{

	if (shell->prompt[0] == '\0')
		return (0);
	shell->eco_token = lectur_imput(shell->prompt, shell->env);
	if (!shell->eco_token)
		return (-1);
	shell->cmds = token_to_cmd(shell->eco_token);
	if (executor(shell) == -1)
		return (-1);
	return (0);
}
