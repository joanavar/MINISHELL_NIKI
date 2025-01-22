/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:09:50 by camurill          #+#    #+#             */
/*   Updated: 2025/01/22 16:47:40 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int static	interpretor(char *str)
{
	long	nbr;

	nbr = ft_atoi((const char *)str); //ToDo long
	if (nbr < 0)
		nbr *= -1;
	if (nbr > 255)
		return((nbr % 255) * 255);
	return (nbr);

}

int	mini_exit(t_cmd *cmd)
{
	cmd->shell->exit_status = check_numeric(cmd->arr_cmd[1]);
	printf("check: %s = %i\n", cmd->arr_cmd[1], cmd->shell->exit_status);
	if (cmd->shell->exit_status == 0)
	{
		if (!cmd->arr_cmd[2])
		{
			cmd->shell->exit_status = interpretor(cmd->arr_cmd[1]);
			exit (cmd->shell->exit_status);
		}
		else
		{
			printf("exit\nbash: exit: too many arguments\n");
			return (1);
		}
	}
	else if (cmd->shell->exit_status == 2)
	{
		printf("exit\nbash: exit: %s: numeric argument requeried", cmd->arr_cmd[1]);
		exit (2);
	}
	return (cmd->shell->exit_status);
}
