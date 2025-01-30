/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:09:50 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 17:29:00 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int static	interpretor(char *str)
{
	long	nbr;
	int		sign;

	if (!str)
		return (0);
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	nbr = ft_atoi((const char *)str);
	if (nbr > 255 || nbr < -255)
		return ((nbr * sign) % 256);
	return (nbr);
}

int	mini_exit(t_cmd *cmd)
{
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
			cmd->shell->exit_status = interpretor(cmd->arr_cmd[1]);
			printf(YELLOW "exit\n" GBD);
			clean_data(cmd->shell);
			exit(cmd->shell->exit_status);
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
