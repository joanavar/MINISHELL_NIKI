/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:08:20 by camurill          #+#    #+#             */
/*   Updated: 2025/01/14 17:27:30 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	get_cd(t_cmd *cmd)
{
	if (!cmd->arr_cmd[1])
	{
		error_message("Need a relative or absolute path", NO_CLOSE);
		return ;
	}
	else if (cmd->arr_cmd[1])
	{
		if (chdir(cmd->arr_cmd[1]) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else
	{
		error_message("Too many arguments\n", NO_CLOSE);
		return ;
	}
}
