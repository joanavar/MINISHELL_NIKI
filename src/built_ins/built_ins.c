/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:50:29 by camurill          #+#    #+#             */
/*   Updated: 2025/01/21 14:55:15 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_selector(t_cmd *cmd)
{
	if (!strncmp("exit", cmd->arr_cmd[0], 5))
	{
		if (!cmd->arr_cmd[1])
		{
			printf(YELLOW"exit\n"GBD);
			clean_data(&cmd->shell);
			exit(0);
		}
		else
			return (mini_exit(cmd));
	}
	if (!strncmp("env", cmd->arr_cmd[0], 4))
		print_env(cmd->shell);
	if (!strncmp("pwd", cmd->arr_cmd[0], 4) && !cmd->arr_cmd[1])
		get_pwd();
	else if (!strncmp("pwd", cmd->arr_cmd[0], 4) && cmd->arr_cmd[1])
		error_message("pwd: too many arguments", NO_CLOSE);
	if (!strncmp("cd", cmd->arr_cmd[0], 3))
		get_cd(cmd);
	return (0);
}
int	built_ins(t_cmd	*cmd) //corregir errores
{
	if (ft_selector(cmd) == -1)
		return (-1);
	if (!strncmp("export", cmd->arr_cmd[0], 7))
		get_export(cmd);//ToDo
	if (!strncmp("unset", cmd->arr_cmd[0], 6))
		unset_shell(cmd->shell, cmd->arr_cmd[1]);
	if (!strncmp("echo", cmd->arr_cmd[0], 5))
		get_echo(cmd);
	return (0);
}
