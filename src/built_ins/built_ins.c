/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:50:29 by camurill          #+#    #+#             */
/*   Updated: 2024/12/14 20:32:16 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_ins(t_shell *shell) //corregir errores
{
	if (!shell->eco_token->content || shell->eco_token->content[0] == '\0')
		return (0);
	if (!strncmp("exit", shell->eco_token->content, 5))
	{
		printf(YELLOW"exit\n"GBD);
		if (shell->eco_token->next)
		{
			printf("minishell: exit: %s: ", shell->arg[1]);
			printf("numeric argument required\n");
		}
		return (-1);
	}
	if (!strncmp("env", shell->eco_token->content, 4))
		print_env(shell);
	if (!strncmp("pwd", shell->eco_token->content, 4) && !shell->eco_token->next)
		get_pwd();
	else if (!strncmp("pwd", shell->eco_token->content, 4) && shell->eco_token->next)
		error_message("pwd: too many arguments", NO_CLOSE);
	if (!strncmp("cd", shell->eco_token->content, 3))
		get_cd(shell);
	if (!strncmp("export", shell->eco_token->content, 7))
		get_export(shell);
	if (!strncmp("unset", shell->eco_token->content, 6))
		unset_shell(shell, shell->eco_token->next->next->content);
	if (!strncmp("echo", shell->eco_token->content, 5))
		get_echo(shell);
	return (0);
}
