/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:09:50 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 20:37:41 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int static	interpretor(char *str)
{
	long	nbr;

	if (!str)
		return (0);
	nbr = ft_atoi((const char *)str);
	if (nbr > 255 || nbr < -255)
		nbr = nbr % 256;
	return (nbr);
}

int	mini_exit(t_cmd *cmd)
{
	int	i;
	
	if (!cmd || !cmd->shell || !cmd->arr_cmd)
	{
		printf("Error: Invalid command structure\n");
		exit(1);
	}
	if (!cmd->arr_cmd[1])
	{
		printf(YELLOW "exit\n" GBD);
		clean_data(cmd->shell);
		exit(cmd->shell->exit_status);
	}
	cmd->shell->exit_status = check_numeric(cmd->arr_cmd[1]);
	if (cmd->shell->exit_status == 0)
	{
		if (!cmd->arr_cmd[2])
		{
			i = interpretor(cmd->arr_cmd[1]);
			printf(YELLOW "exit\n" GBD);
			clean_data(cmd->shell);
			exit(i);
		}
		else
		{
			printf(YELLOW "exit\n" GBD "bash: exit: too many arguments\n");
			return (1);
		}
	}
	else if (cmd->shell->exit_status == 2)
	{
		printf(YELLOW "exit\n" GBD "bash: exit: %s: numeric argument required\n",
			cmd->arr_cmd[1]);
		clean_data(cmd->shell);
		exit(2);
	}
	return (cmd->shell->exit_status);
}
