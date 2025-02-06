/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:50:29 by camurill          #+#    #+#             */
/*   Updated: 2025/02/06 17:59:25 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_selector(t_cmd *cmd)
{
	if (!ft_strncmp("exit", cmd->arr_cmd[0], 5))
	{
		if (!cmd->arr_cmd[1])
		{
			printf(YELLOW "exit\n" GBD);
			clean_data(cmd->shell);
			exit(0);
		}
		else
			return (mini_exit(cmd));
	}
	if (!ft_strncmp("env", cmd->arr_cmd[0], 4))
		print_env(cmd->shell, cmd);
	if (!ft_strncmp("pwd", cmd->arr_cmd[0], 4) && !cmd->arr_cmd[1])
		get_pwd();
	else if (!ft_strncmp("pwd", cmd->arr_cmd[0], 4) && cmd->arr_cmd[1])
		error_message("pwd: too many arguments", NO_CLOSE);
	if (!ft_strncmp("cd", cmd->arr_cmd[0], 3))
		get_cd(cmd);
	return (0);
}

static int	aux_built_ins(t_cmd *cmd, t_trust *trust)
{
	if (ft_selector(cmd) == -1)
		return (-1);
	if (!ft_strncmp("export", cmd->arr_cmd[0], 7))
		get_export(cmd, trust);
	if (!ft_strncmp("unset", cmd->arr_cmd[0], 6))
		unset_shell(cmd->shell, cmd->arr_cmd[1]);
	if (!ft_strncmp("echo", cmd->arr_cmd[0], 5))
		get_echo(cmd);
	return (0);
}

/*static void	close2_dups(t_cmd *cmd)
{
	if (cmd->std_in != 0)
	{
		close(cmd->std_in);
		dup2(cmd->std_dup, 0);
		close(cmd->std_dup);
	}
	if (cmd->std_out != 1)
	{
		close(cmd->std_out);
		dup2(cmd->stdout_dup, 1);
		close(cmd->stdout_dup);
	}
}*/

static int	pid_builtins(t_cmd *cmd, t_trust *trust)
{
	t_cmd	*aux;

	aux = cmd;
	ft_dups(aux);
	if (aux_built_ins(aux, trust) == 1)
		return (-1);
	//close2_dups(aux);
	return (-1);
}

int	built_ins(t_cmd *cmd, int type, t_trust *trust)
{
	int	ln;

	ln = 0;
	if (type == 0 && !cmd->redirs)
		ln = aux_built_ins(cmd, trust);
	else
		ln = pid_builtins(cmd, trust);
	return (ln);
}
