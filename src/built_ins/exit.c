/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:43:42 by nikitadorof       #+#    #+#             */
/*   Updated: 2025/01/31 16:29:31 by nikitadorof      ###   ########.fr       */
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

static int	aux_exit(t_cmd *cmd)
{
	int	i;

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
		printf(YELLOW "exit\n" GBD);
		printf("bash: exit: %s: numeric argument required\n", cmd->arr_cmd[1]);
		clean_data(cmd->shell);
		exit(2);
	}
	return (cmd->shell->exit_status);
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
		if (cmd->shell->eco_token)
			free_token(&(cmd->shell->eco_token));
		clean_data(cmd->shell);
		exit(cmd->shell->exit_status);
	}
	cmd->shell->exit_status = check_numeric(cmd->arr_cmd[1]);
	return (aux_exit(cmd));
}
