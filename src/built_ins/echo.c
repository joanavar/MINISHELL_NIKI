/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:42:39 by camurill          #+#    #+#             */
/*   Updated: 2025/01/28 15:34:38 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_echo(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (!cmd->arr_cmd[1])
		printf("\n");
	else if (cmd->arr_cmd[1] && !strncmp("-n", cmd->arr_cmd[1], 3))
	{
		if (!cmd->arr_cmd[2])
			return ;
		i = 1;
		while (cmd->arr_cmd[++i])
			printf("%s", cmd->arr_cmd[i]);
	}
	else if (cmd->arr_cmd[1] && strncmp("-n", cmd->arr_cmd[1], 3))
	{
		while (cmd->arr_cmd[++i])
		{
			if (!cmd->arr_cmd[i + 1])
				printf("%s\n", cmd->arr_cmd[i]);
			else
				printf("%s ", cmd->arr_cmd[i]);
		}
	}
}
